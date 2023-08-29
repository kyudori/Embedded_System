#include "mbed.h"

AnalogOut led(DAC0_OUT); // led = DAC0_OUT

int main()
{
    float f;

    while(true) {
        for(f = 0.5; f <= 1.0; f = f + 0.01) { // on LED from 50% - 100%
            led.write(f);
            thread_sleep_for(3000/50);
        }
        for(f = 1.0; f >= 0.5; f = f - 0.01) { // on LED from 50% - 100%
            led.write(f);
            thread_sleep_for(3000/50);
        }
    }
}