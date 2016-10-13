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
    int divider = BUFFER_SIZE / BIN_NUMBER / 2;
    float result = 0;
    int *output = new int[BIN_NUMBER];

    for (int i = 0; i < BIN_NUMBER; i++) {
        output[i] = 0;
    }

    for (int i = 1; i < BUFFER_SIZE / 2; i += divider) {
        for (int j = i; j < i * divider; j++) {
            result += frequencies[i].power;
        }

        result = floor(result / divider * 1 / MAX_SIGNAL_POS_VALUE);
        output[i] = result;


        result = 0;
        cout << output[i] << ", ";
    }
    cout << endl;

    return output;
}

