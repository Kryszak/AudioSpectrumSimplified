/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FrequencyBin.h
 * Author: kryszak
 *
 * Created on 13 października 2016, 13:07
 */

#ifndef FREQUENCYBIN_H
#define FREQUENCYBIN_H

class FrequencyBin {
public:
    FrequencyBin();
    FrequencyBin(const FrequencyBin& orig);
    virtual ~FrequencyBin();
    
    float power;
    int frequency;
private:

};

#endif /* FREQUENCYBIN_H */

