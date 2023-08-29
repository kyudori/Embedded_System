#include "mbed.h"

DigitalOut led1(LED1);               // led = LED1

int main()
{
    int i;

    while (true) {
        for(i = 0; i < 3; i++){
            led1 = 0;
            thread_sleep_for(300);
            led1 = 1;
            thread_sleep_for(300);
        }
        thread_sleep_for(1000);

         for(i = 0; i < 3; i++){
            led1 = 0;
            thread_sleep_for(1000);
            led1 = 1;
            thread_sleep_for(300);
        }
        thread_sleep_for(1000);
    }
}