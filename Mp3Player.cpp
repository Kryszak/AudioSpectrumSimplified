/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mp3Player.cpp
 * Author: kryszak
 * 
 * Created on 13 października 2016, 13:03
 */

#include "Mp3Player.h"

Mp3Player::Mp3Player() {
}

Mp3Player::Mp3Player(char* path) {
    this->init(path);
}

Mp3Player::~Mp3Player() {
    //usuniecie buforow
    delete buffer;
    delete ledDriver;
    //zamkniecie uchwytow ao i mpg123
    ao_close(device);
    mpg123_close(mh);
    mpg123_delete(mh);
    //zamkniecie ao i mpg123
    mpg123_exit();
    ao_shutdown();
}

void Mp3Player::init(char* path) {
    this->path = path;
    //inicjalizacja biblioteki ao
    ao_initialize();
    driver = ao_default_driver_id();

    //inicjalizacja biblioteki mpg123
    mpg123_init();
    mh = mpg123_new(NULL, &err);

    //ustawienie rozmiarow buforow
    bufferSize = BUFFER_SIZE;
    buffer = new unsigned char[bufferSize];
    
    ledDriver = new LedDriver();
}

float Mp3Player::scale(kiss_fft_scalar val) {
    return val < 0 ? val * (1 / MAX_SIGNAL_NEG_VALUE) : val * (1 / MAX_SIGNAL_POS_VALUE);
}

/*
 *Zsumowanie lewego i prawego kanalu
 *Format PCM:
 * 2 kolejne bajty - lewy kanal, 2 nastepne - prawy kanal 
 * Zsumowanie obu kanalow
 */
void Mp3Player::demux(char* in, short out[]) {
    short left[bufferSize / 2];
    short right[bufferSize / 2];
    int index = 0;

    for (int i = 0; i < bufferSize * 2; i += 4) {
        left[index] = in[i] | (in[i + 1] << 8);
        right[index] = in[i + 2] | (in[i + 3] << 8);
        index++;
    }

    for (int i = 0; i < bufferSize / 2; i++) {
        out[i] = left[i] + right[i];
    }

}

void Mp3Player::run() {
    int err;
    err = mpg123_open(mh, path); //otwarcie pliku; sprawdzic, co zwraca, zlapac wyjatek

    if (err == -1) {
        cout << "Cannot find file(readers.h error)" << endl;
    }

    mpg123_getformat(mh, &rate, &channels, &encoding); //sprawdzenie formatu pliku


    //czary ustawiajace parametry do odtwarzania ao
    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;

    device = ao_open_live(driver, &format, NULL); //otwarcie odtwarzania


    int samples = bufferSize / 4; //ilosc probek przekazywanych do fft

    //bufory do fft
    kiss_fft_cpx in[samples];
    kiss_fft_cpx out[samples];
    kiss_fft_cfg cfg;

    short signal[samples];

    //zerowanie czesci urojonej buforow
    for (int i = 0; i < samples; i++) {
        in[i].i = 0;
    }

    cfg = kiss_fft_alloc(samples, 0, 0, 0); //alokacja pamieci buforow fft

    //glowna petla odtwarzajaca i przetwarzajaca dane
    while (mpg123_read(mh, buffer, bufferSize, &done) == MPG123_OK) {

        demux((char*) buffer, signal);

        //wrzucenie probek, przemnozenie przez okno Hanna
        for (int i = 0; i < samples; i++) {
            in[i].r = signal[i] * 0.5f * (1 - cos(2 * M_PI * i / (samples - 1)));
        }

        kiss_fft(cfg, in, out); //wykonaj fft

        for (int i = 0; i < samples; i++) {
            float real = (out[i].r);
            float imaginary = (out[i].i);
            fft_result[i].power = scale(real * real + imaginary * imaginary);
            fft_result[i].frequency = i * rate / samples;
        }
        int *tab = Utils::formatOutput(fft_result);
        unsigned char *tab1 = Utils::convertOutput(tab);
        //this->ledDriver->visualize(tab1);
        delete(tab);
        delete(tab1);
        ao_play(device, (char*) buffer, done); //odtworz pobrana probke
    }
    free(cfg); //usun niepotrzebne zmienne kiss_fft
}

void Mp3Player::setPath(char* path) {
    this->path = path;
}
