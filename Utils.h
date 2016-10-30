/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utils.h
 * Author: kryszak
 *
 * Created on 13 października 2016, 14:25
 */

#ifndef UTILS_H
#define UTILS_H

#include "FrequencyBin.h"
#include <iostream>
#include "Constants.h"
#include <math.h>

using namespace std;

class Utils {
public:
    Utils();
    virtual ~Utils();
    static int* formatOutput(FrequencyBin[]);
    static unsigned char* convertOutput(int[]);
};

#endif /* UTILS_H */

