#include "mbed.h"

SPI spi(PTD2, PTD3, PTD1); // spi = (MOSI, MISO, SCLK)
DigitalOut ss(PTD0, 0x01); // ss = PTD0
DigitalIn sw(D0, PullDown); // sw = D0(PullDown)

int main()
{
    spi.format(8, 3); // 8-bit data, mode 3
    spi.frequency(1000000); // frequency 1,000,000 Hz
    while(true) {
        if(sw == 1) { // if sw is on
        ss = 0; // enable slave
        spi.write('1'); // send '1' and receive
        ss = 1; // disable slave
        thread_sleep_for(200); // wait 200 ms
        } 
    }
}