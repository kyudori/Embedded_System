#include "mbed.h"
// display = bus of D0-D7
BusOut display(D0, D1, D2, D3, D4, D5, D6, D7);

int main()
{
    while (true) {
        for(int i = 0; i <= 16; i++){
            switch (i){
                case 0:
                display = 0x3F;
                break;
                case 1:
                display = 0x06;
                break;
                case 2:
                display = 0x5B;
                break;
                case 3:
                display = 0x4F;
                break;
                case 4:
                display = 0x66;
                break;
                case 5:
                display = 0x6D;
                break;
                case 6:
                display = 0x7D;
                break;
                case 7:
                display = 0x07;
                break;
                case 8:
                display = 0x7F;
                break;
                case 9:
                display = 0x6F;
                break;
                case 10:
                display = 0x77;
                break;
                case 11:
                display = 0x7C;
                break;
                case 12:
                display = 0x39;
                break;
                case 13:
                display = 0x5E;
                break;
                case 14:
                display = 0x79;
                break;
                case 15:
                display = 0x71;
                break;
                default:
                break;
            }
            thread_sleep_for(1000);

        }
    }
}