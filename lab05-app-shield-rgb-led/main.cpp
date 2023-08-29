#include "mbed.h"
#include "C12832.h"

C12832 lcd(D11, D13, D12, D7, D10); // lcd = (MOSI, SCK, RESET, A0, nCS)
PwmOut led_r(D5); // led_r = (Red LED)
PwmOut led_g(D9); // led_g = (Red LED)
PwmOut led_b(D8); // led_b = (Red LED)

int main()
{
    lcd.cls();
    lcd.locate(0, 6);
    lcd.printf("RGB LED!");
    while(true) {
        for(float f = 0.0; f < 1.0; f += 0.05) {
            led_r = 1.0 - f; // on LED Red
            led_g = 1.0; // off LED Green
            led_b = 1.0; // off LED Blue
            lcd.locate(0, 16);
            lcd.printf("Red=%.2f, Green=%.2f, Blue=%.2f", f, 0.0, 0.0);
            thread_sleep_for(10);
        }
        for(float f = 0.0; f < 1.0; f += 0.05) {
            led_r = 1.0; // off LED Red
            led_g = 1.0 - f; // on LED Green
            led_b = 1.0; // off LED Blue
            lcd.locate(0, 16);
            lcd.printf("Red=%.2f, Green=%.2f, Blue=%.2f", 0.0, f, 0.0);
            thread_sleep_for(10);
        }
        for(float f = 0.0; f < 1.0; f += 0.05) {
            led_r = 1.0; // off LED Red
            led_g = 1.0; // off LED Green
            led_b = 1.0 - f; // on LED Blue
            lcd.locate(0, 16);
            lcd.printf("Red=%.2f, Green=%.2f, Blue=%.2f", 0.0, 0.0, f);
            thread_sleep_for(10);
        }
    }
}