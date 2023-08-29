#include "mbed.h"

AnalogOut vout(DAC0_OUT); // vout = DAC0_OUT

int main()
{
    unsigned short v;

    while(true) {
        v = 0xFFFF * (1.5 / 3.3); // 1.5 V when VDD = 3.3V
        vout.write_u16(v);
        thread_sleep_for(1000);
    }
}