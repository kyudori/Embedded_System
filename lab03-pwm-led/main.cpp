#include "mbed.h"

PwmOut led(PTA1); // led = PTA1

int main()
{
    float duty;
    led.period(10.0 / 1000);
    while (true) {
        for(duty = 0.0; duty < 1.1; duty = duty + 0.1) {
         led.write(duty);
         thread_sleep_for(1000);
        }
    }
}