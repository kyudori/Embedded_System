#include "mbed.h"
#include "C12832.h"
#include "LM75B.h"

C12832 lcd(D11, D13, D12, D7, D10); // lcd = (MOSI, SCK, RESET, A0, nCS)
LM75B temp(D14, D15); // temp = (SDA, SCL)

int main()
{
    lcd.cls();
    lcd.locate(0, 6);
    lcd.printf("Current temperature!");
    while(true) {
        lcd.locate(0, 16);
        lcd.printf("%5.2f degree Celsius", temp.read());
        thread_sleep_for(1000);
    }
}