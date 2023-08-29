#include "mbed.h"
#include "C12832.h"
#include "MMA7660.h"

C12832 lcd(D11, D13, D12, D7, D10); // lcd = (MOSI, SCK, RESET, A0, nCS)
MMA7660 MMA(D14, D15); // MMA = (I2C_SDA, I2C_SCL)

int main()
{
    lcd.cls();
    lcd.locate(0, 6);
    lcd.printf("Mbed 3-Axis accelerometer!");
    while(true) {
       lcd.locate(0, 16);
        lcd.printf("x=%.2f y=%.2f z=%.2f", MMA.x(), MMA.y(), MMA.z());
        thread_sleep_for(100);
    }
}