#include "mbed.h"

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

void thread_2() {
    while (true) {
        mutex.lock();
        for (int i = 0; i < 50; i++) printf("2");
        printf("\r\n");
        mutex.unlock();
    }
}

void thread_3() {
    while (true) {
        mutex.lock();
        for (int i = 0; i < 50; i++) printf("3");
        printf("\r\n");
        mutex.unlock();
    }
}

int main(){
    thread1.start(thread_1); thread2.start(thread_2);
    thread3.start(thread_3);
    while (true) ;

}

mutex-no

#include "mbed.h"

Thread thread1, thread2, thread3; // threads


void thread_1() {
    while (true) {
        for (int i = 0; i < 50; i++) printf("1");
        printf("\r\n");
    }
}

void thread_2() {
    while (true) {
        for (int i = 0; i < 50; i++) printf("2");
        printf("\r\n");
    }
}

void thread_3() {
    while (true) {
        for (int i = 0; i < 50; i++) printf("3");
        printf("\r\n");
    }
}

int main(){
    thread1.start(thread_1); thread2.start(thread_2);
    thread3.start(thread_3);
    while (true) ;

}