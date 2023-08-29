#include "mbed.h"
#include "C12832.h"

C12832 lcd(D11, D13, D12, D7, D10); // lcd = (MOSI, SCK, RESET, A0, nCS)
AnalogIn pot1(A0); // pot1 = A0
AnalogIn pot2(A1); // pot2 = A1
PwmOut led_r(D5); // led_r = (Red LED)
PwmOut led_g(D9); // led_g = (Green LED)

int main()
{
    lcd.cls();
    lcd.locate(0, 6);
    lcd.printf("Rotate Potentiometers!");
    while(true) {
        lcd.locate(0, 16);
        lcd.printf("Pot1=%4.2f, Pot2=%4.2f", pot1.read(), pot2.read());
        led_r = 1.0 - pot1.read(); // pot1 -> Red LED
        led_g = 1.0 - pot2.read(); // pot2 -> Green LED
        thread_sleep_for(200);
    }
}