#include "LedDriver.h"

LedDriver::LedDriver() {
    if (!bcm2835_init()) {
        cout << "Could not initialize BCM2835 library!" << endl;
        return;
    }

    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
    bcm2835_gpio_fsel(Max7219_pinCS, BCM2835_GPIO_FSEL_OUTP);
}

LedDriver::~LedDriver() {
    clearMatrix();

    bcm2835_spi_end();
    bcm2835_close();
}

void LedDriver::visualize(uchar data[]) {
    clearMatrix();
    for (int i = 1; i < 9; i++) {
        writeMax7219(i, data[i - 1], i, data[i + 7]);
    }
}

void LedDriver::delayXms(uint x) {
    //	bcm2835_delay(x);
}

void LedDriver::writeMax7219Byte(uchar DATA) {
    bcm2835_gpio_write(Max7219_pinCS, LOW);
    bcm2835_spi_transfer(DATA);
}

void LedDriver::writeMax7219(uchar address1, uchar dat1, uchar address2, uchar dat2) {
    bcm2835_gpio_write(Max7219_pinCS, LOW);

    writeMax7219Byte(address1);
    writeMax7219Byte(dat1);
    writeMax7219Byte(address2);
    writeMax7219Byte(dat2);

    bcm2835_gpio_write(Max7219_pinCS, HIGH);
}

void LedDriver::clearMatrix() {
    int i;
    for (i = 1; i < 9; i++) {
        writeMax7219(i, CLEAR_ROW, i, CLEAR_ROW);
    }
}
