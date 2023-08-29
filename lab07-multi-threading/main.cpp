#include "mbed.h"

Serial pc(USBTX, USBRX, 115200); // baud rate 115200
Thread thread1, thread2, thread3; // Three threads

void thread_1()
{
    static int t = 0;
    while (true) {
        printf("\r\n[%d]: ", t++);ThisThread::sleep_for(1000);
    }
}

void thread_2()
{
    while (true) {
        ThisThread::sleep_for(2000);
        printf("thread_2 ");
    }
}

void thread_3()
{
    while (true) {
        ThisThread::sleep_for(3000);
        printf("thread_3 ");
    }
}

int main()
{
    thread1.start(thread_1); 
    thread_sleep_for(10);
    thread2.start(thread_2); 
    thread_sleep_for(10);
    thread3.start(thread_3);
    thread_sleep_for(20 * 1000);
    thread3.terminate(); thread2.terminate(); thread1.terminate();
    
    while (true);
}