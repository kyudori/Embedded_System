#include "mbed.h"

I2C i2c(I2C_SDA, I2C_SCL); // i2c = (I2C_SDA, I2C_SCL)
DigitalIn sw(D0, PullDown); // sw = D0(PullDown)

const int addr = 0xa0; // slave addr (even no)

int main()
{
    while(true) {
        if(sw == 1) { // if sw is on
            i2c.start(); // start condition
            i2c.write(addr | 0x00); // write (addr | WRITE)
            i2c.write('1'); // write '1'
            i2c.stop(); // stop condition
            thread_sleep_for(200); // wait 200 ms
        }
    }
}