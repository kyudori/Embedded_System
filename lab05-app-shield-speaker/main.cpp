#include "mbed.h"
#include "C12832.h"
#include "pitches.h"

C12832 lcd(D11, D13, D12, D7, D10); // lcd = (MOSI, SCK, RESET, A0, nCS)
PwmOut speaker(D6); // speaker = D6

int length = 75;
float frequency[] = {
    NOTE_E6, NOTE_E6, 0, NOTE_E6, 0, NOTE_C6, NOTE_E6, 0, NOTE_G6, 0, 0,
    0, NOTE_G5, 0, 0, 0, NOTE_C6, 0, 0, NOTE_G5, 0, 0, NOTE_E5, 0, 0,
    NOTE_A5, 0, NOTE_B5, 0, NOTE_AS5, NOTE_A5, 0, NOTE_G5, NOTE_E6, NOTE_G6,
    NOTE_A6, 0, NOTE_F6, NOTE_G6, 0, NOTE_E6, 0, NOTE_C6, NOTE_D6, NOTE_B5,
    0, 0, NOTE_C6, 0, 0, NOTE_G5, 0, 0, NOTE_E5, 0, 0, NOTE_A5, 0, NOTE_B5,
    0, NOTE_AS5, NOTE_A5, 0, NOTE_G5, NOTE_E6, NOTE_G6, NOTE_A6, 0, NOTE_F6,
    NOTE_G6, 0, NOTE_E6, 0, NOTE_C6, NOTE_D6, NOTE_B5, 0, 0
};

float beat[] = {
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12,
};

int main()
{
    lcd.cls(); lcd.locate(0, 6); lcd.printf("Listen to speaker!");
    lcd.locate(0, 16); lcd.printf("Mario~~~");
    while(true) {
        for(int i = 0; i <= length; i++) {
            if(frequency[i] == 0) {
                speaker = 0.0;
            } else {
                speaker.period(1.0 / frequency[i]);  // period = (1.0 / frequency)
                speaker = 0.5;                       // duty cycle = 50%
            }
            thread_sleep_for(2500.0 / beat[i]);     // duration = (C / beat) ms
        }
    }
}