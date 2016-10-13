/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mp3Player.h
 * Author: kryszak
 *
 * Created on 13 października 2016, 13:03
 */

#ifndef MP3PLAYER_H
#define MP3PLAYER_H

#include <iostream>
#include <mpg123.h>
#include <ao/ao.h>
#include <math.h>
#include "FrequencyBin.h"
#include "kiss_fft/kiss_fft.h"

#define BITS 8
#define BUFFER_SIZE 4096
#define MAX_SIGNAL_NEG_VALUE 32768.0f
#define MAX_SIGNAL_POS_VALUE 32767.0f

using namespace std;

class Mp3Player {
public:
    Mp3Player();
    Mp3Player(char*);
    virtual ~Mp3Player();
    
    void setPath(char*);
    FrequencyBin fft_result[BUFFER_SIZE / 2];
    void run();
private:
 //zmienne mpg123 
    mpg123_handle *mh;
    size_t done;
    int err;
    unsigned char *buffer;
    //zmienne audio info ao
    int driver;
    int channels;
    int encoding;
    long rate;
    //zmienne libao
    ao_device *device;
    ao_sample_format format;
    size_t bufferSize; //rozmiar bufora
    const char* path = NULL; //sciezka do pliku
    
    float scale(kiss_fft_scalar);
    void demux(char*, short[]);
    void init(char*); 
};

#endif /* MP3PLAYER_H */

