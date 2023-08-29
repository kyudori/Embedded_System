#include "mbed.h"

SPISlave spi_slave(PTD2, PTD3, PTD1, PTD0); // spi_slave = (MOSI, MISO, SCLK, SS)
DigitalOut led(D0); // led = D0

int main()
{
    unsigned char r;

    spi_slave.format(8, 3); // 8-bit data, mode 3
    spi_slave.frequency(1000000); // frequency 1,000,000 Hz
    led = 0;
    while(true) {
        if(spi_slave.receive()) { // if spi data is ready
            r = spi_slave.read(); // r = receive data
            spi_slave.reply(r); // and send r
            if(r == '1') { // if r == '1'
                led = 1; // on LED
                thread_sleep_for(200); // wait for 200 ms
                led = 0; // off LED
            }
        }
    }
}