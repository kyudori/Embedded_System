#include "mbed.h"

I2CSlave i2c_slave(I2C_SDA, I2C_SCL); // i2c_slave = (I2C_SDA, I2C_SCL)
DigitalOut led(D0); // led = D0
const int addr = 0xa0; // slave addr (even no)

int main() 
{
    int i, r;
    led = 0;
    i2c_slave.address(addr); // set slave address
    while(true) {
        i = i2c_slave.receive(); // check if my address is selected
        switch(i) {
        case I2CSlave::WriteAddressed: // WRITE means slave read
            i2c_slave.read(); // read address skips
            r = i2c_slave.read(); // r = read data
            if(r == '1') { // if r == '1'
                led = 1; // on led
                thread_sleep_for(200); // wait 200 ms
                led = 0; // off led
            }
            break;
        default:
            break;
        }
    }
}