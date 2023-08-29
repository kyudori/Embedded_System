#include "mbed.h"

Serial uart_rx(D1, D0); // uart_rx = (D1=TX, D0=RX)
DigitalOut led(D2); // led = D2

int main()
{
    while(true) {
        if(uart_rx.getc() == '1') { // if getc() is '1'
            led = 1; // on LED
            thread_sleep_for(200); // wait 200 ms
            led = 0; // off LED
        }
    }
}