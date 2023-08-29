#include "mbed.h"

DigitalOut led(D0);               // led = LED1
DigitalIn sw(D1);

int main()
{
    while (true) {
        if(sw == 1) {
            led = 1;
            thread_sleep_for(200);
            led = 0;
            thread_sleep_for(200);
            led = 1;
            thread_sleep_for(200);
            led = 0;
        }
    }
}