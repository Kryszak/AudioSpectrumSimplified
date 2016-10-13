/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kryszak
 *
 * Created on 13 października 2016, 13:02
 */

#include <cstdlib>
#include "Mp3Player.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Mp3Player *player = new Mp3Player("/home/kryszak/eldorado.mp3");
    
    player->run();
    
    delete player;
    
    return 0;
}

