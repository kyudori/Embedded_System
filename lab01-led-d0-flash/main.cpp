#include "mbed.h"

// https://os.mbed.com/docs/mbed-os/v5.15/tools/creating-a-new-program.html

Serial pc(USBTX, USBRX, 115200);    // baud rate 115200
DigitalOut led(LED1);               // led = LED1

int main()
{
    while (true) {
        led = 0;
        printf("LED1 is ON\r\n");
        thread_sleep_for(500);
        led = 1;
        printf("LED1 is OFF\r\n");
        thread_sleep_for(500);
    }
}