#include "mbed.h"
#include "C12832.h"

C12832 lcd(D11, D13, D12, D7, D10); // lcd = (MOSI, SCK, RESET, A0, nCS)
DigitalIn up(A2); // up = A1
DigitalIn down(A3); // down = A3
DigitalIn left(A4); // left = A4
DigitalIn rite(A5); // rite = A5
DigitalIn center(D4); // center = D4

int main()
{
    lcd.cls();
    lcd.locate(0, 6);
    lcd.printf("Move Joystick!");
    while(true) {
        if(up) { // if up
        lcd.locate(0, 16);
        lcd.printf("Up ");
        }
        if(down) { // if down
        lcd.locate(0, 16);
        lcd.printf("Down ");
        }
        if(left) { // if left
        lcd.locate(0, 16);
        lcd.printf("Left ");
        }
        if(rite) { // if right
        lcd.locate(0, 16);
        lcd.printf("Right ");
        }
        if(center) { // if center
        lcd.locate(0, 16);
        lcd.printf("Center ");
        }
        thread_sleep_for(200);
    }
}