/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utils.cpp
 * Author: kryszak
 * 
 * Created on 13 października 2016, 14:25
 */

#include <cmath>

#include "Utils.h"

Utils::Utils() {
}

Utils::~Utils() {
}

int* Utils::formatOutput(FrequencyBin frequencies[]) {
    int divider = BUFFER_SIZE / BINS_NUMBER / 2;
    float result = 0;
    int *output = new int[BINS_NUMBER];

    for (int i = 0; i < BINS_NUMBER; i++) {
        output[i] = 0;
    }

    for (int i = 1; i < BUFFER_SIZE / 2; i += divider) {
        for (int j = i; j < i * divider; j++) {
            result += frequencies[i].power;
        }

        result = floor(result / divider * 1 / MAX_SIGNAL_POS_VALUE);
        output[i] = result;

        result = 0;
    }

    return output;
}

unsigned char* Utils::convertOutput(int output[]) {
    unsigned char* result = new unsigned char[BINS_NUMBER];

    unsigned char led_row = 0x00;

    for (int i = 0; i < LED_HEIGHT; i++) {
        for (int j = 0; j < BINS_NUMBER / 2; j++) {
            if (output[j] > 0) {
                led_row |= 1 << j;
                output[j] -= 1;
            }
        }
        result[i] = led_row;
        led_row = 0x00;
        for (int j = BINS_NUMBER / 2; j < BINS_NUMBER; j++) {
            if (output[j] > 0) {
                led_row |= 1 << (j % 8);
                output[j] -= 1;
            }
        }
        result[i + 8] = led_row;
        led_row = 0x00;
    }

    return result;
}

