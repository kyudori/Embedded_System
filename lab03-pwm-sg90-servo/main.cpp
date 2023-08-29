#include "mbed.h"

PwmOut servo(PTA1); // servo = PTA1

int main()
{
    float w;
    servo.period(20.0/1000.0); // period = 20 ms for SG90 Servo
    
    while(true) {
    // 500 to 2,500 us for degree 0 to 180
        for(w = 500; w <= 2500; w = w + 100) {
            servo.write(w / (20.0 * 1000.0));
            thread_sleep_for(1000);
        }
    }   
}