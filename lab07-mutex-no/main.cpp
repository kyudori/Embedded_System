#include "mbed.h"

//...
Thread thread1, thread2, thread3; // threads
Mutex mutex; // mutex

void thread_1() {
    while (true) {
    mutex.lock();
    for (int i = 0; i < 50; i++) printf("1");
    printf("\r\n");
    mutex.unlock();
    }
    }
//...