#include "mbed.h"
#include "C12832.h"

C12832 lcd(D11, D13, D12, D7, D10);
PwmOut led_r(D5);
PwmOut led_g(D9);
InterruptIn sw2(SW2); // sw2 = SW2
InterruptIn sw3(SW3);
InterruptIn up(A2); // up = A1
InterruptIn down(A3);
InterruptIn left(A4);
InterruptIn rite(A5);
InterruptIn center(D4);
Timer timer; // timer
int start = 0;
long offset = 0;

void ISR_sw2() {
    if (start == 0) { // if not started
        timer.start(); // start timer
        led_g = 0;
        start = 1;
    } else { // else
        timer.stop();
        led_g = 1.0;
        start = 0;
    }
}

void ISR_sw3(){
    timer.reset();
    offset = 0;
}

void ISR_up(){
    offset = offset + (60*1000);
}

void ISR_down(){
    offset = offset - (60*1000);
}

void ISR_left(){
    offset = offset - (60*60*1000);
}

void ISR_rite(){
    offset = offset + (60*60*1000);
}

void ISR_center(){
    offset = offset - ((timer.read_ms()+offset) %(1000*60));
}

int main()
{
    long time;
    unsigned char h,m,s,ms;

    led_r = led_g = 1.0;
    sw2.fall(&ISR_sw2);
    sw3.fall(&ISR_sw3);

    up.rise(&ISR_up);
    down.rise(&ISR_down);
    left.rise(&ISR_left);
    rite.rise(&ISR_rite);
    center.rise(&ISR_center);

    lcd.cls();
    lcd.locate(0,6);
    lcd.printf("Digital Clock!");

    while(true){
        time = timer.read_ms();
        if((time + offset) < 0) offset = -time;
        time = time + offset;

        ms = time % 60;
        s = (time / 1000) % 60;
        m = ((time / 1000) / 60) % 60;
        h = ((time / 1000) / (60*60)) % 24;

        lcd.locate(0, 16);
        lcd.printf("Current Time: %02d:%02d:%02d.%02d", h, m, s, ms);

        thread_sleep_for(100);
    }

}