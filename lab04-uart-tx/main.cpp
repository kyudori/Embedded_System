#include "mbed.h"

Serial uart_tx(D1, D0); // uart_tx = (D1=TX, D0=RX)
DigitalIn sw(D2, PullDown); // sw = D2(PullDown)

int main()
{
    while(true) {
        if(sw == 1) { // if sw is on
            uart_tx.putc('1'); // send '1'
            thread_sleep_for(200); // wait 200 ms
        }
    }
}