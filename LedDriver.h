#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include <bcm2835.h>
#include <iostream>
#define uchar unsigned char
#define uint unsigned int
#define Max7219_pinCS  RPI_GPIO_P1_24
#define CLEAR_ROW 0x00

using namespace std;

class LedDriver {
public:
	LedDriver();
	virtual ~LedDriver();
	void visualize(int[]);
private:
	void delayXms(uint);
	void writeMax7219Byte(uchar);
	void writeMax7219(uchar, uchar, uchar, uchar);
	void clearMatrix(void);
};

#endif

