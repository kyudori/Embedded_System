#include "mbed.h"

DigitalOut led1(LED1);               // led1 = LED1

int main()
{
    while (true) {
        led1 = 0;                   // on LED1
        thread_sleep_for(500);      // wait 500 ms
        led1 = 1;                   // off LED1
        thread_sleep_for(500);      // wiat 500 ms
    }
}