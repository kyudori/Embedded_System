#include "mbed.h"
#include "C12832.h"

C12832 lcd(D11, D13, D12, D7, D10); // lcd = (MOSI, SCK, RESET, A0, nCS)
PwmOut led_red(D5); // led_r = (Red LED)
PwmOut led_green(D9); // led_g = (Red LED)

InterruptIn sw2(SW2); // sw2 = SW2
InterruptIn sw3(SW3); // sw3 = SW3

int count_sw2 = 0; int count_sw3 = 0;

void ISR_sw2() {
    led_red = 0; // on led_red
    led_green = 1; // off led_green
    count_sw2++; // increment count_sw2
}

void ISR_sw3() {
    led_red = 1; // on led_red
    led_green = 0; // off led_green
    count_sw3++; // increment count_sw2
}

int main()
{

sw2.rise(&ISR_sw2); // attach ISR_sw2 to sw2
led_red = 0;
sw3.fall(&ISR_sw3); // attach ISR_sw3 to sw3
led_green = 0;

int count = 0;

while(true){
    count++;
    lcd.cls();
    lcd.locate(0, 6);
    lcd.printf("Button ISRs!");
    lcd.locate(0, 16);
    lcd.printf("Loop=%d, SW2=%d, SW3=%d", count, count_sw2, count_sw3);
    ThisThread::sleep_for(100);
    }

}