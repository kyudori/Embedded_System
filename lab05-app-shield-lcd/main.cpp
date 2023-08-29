#include "mbed.h"
#include "C12832.h"

C12832 lcd (D11, D13, D12, D7, D10); // lcd = (MOSI, SCK, RESET, A0, nCS

int main()
{
    int count = 0;
    
    lcd.cls();
    lcd.locate(0, 6);// goto (0,
    lcd.printf("Mbed Application Shield!"); // print message
    while(true) {
        lcd.locate(0, 16);// goto (0,
        lcd.printf("Counting: %d", count++); // print count
        thread_sleep_for(1000);
    }
}