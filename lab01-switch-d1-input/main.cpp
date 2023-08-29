#include "mbed.h"

DigitalIn sw(D1, PullDown);          // sw = D1(PullDown)
DigitalOut led1(LED1);               // led1 = LED1

int main()
{
    while (true) {
        if(sw == 1) {
            led1 = 0;
        }   else {
            led1 = 1;
        }
    }
}