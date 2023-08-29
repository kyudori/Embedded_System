#include "mbed.h"

AnalogOut vout(DAC0_OUT);

int main()
{
    float f;
    int t = 0, i;

    printf("Time, Vout\r\n");
    for(f = 0.0; f < 1.1; f = f + 0.1){ // f = 0.0 - 1.0
        vout = f;
        for(i = 0; i < 10; i = i + 1)
            printf("%d, %f\r\n", t++, f * 3.3); // vout = f * 3.3
    }
    for(f = 0.0; f < 1.1; f = f + 0.1){ // f = 0.0 - 1.0
        vout = f;
        for(i = 0; i < 10; i = i + 1)
            printf("%d, %f\r\n", t++, f * 3.3); // vout = f * 3.3
    }
    while(true);
}