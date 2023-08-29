#include "mbed.h"
#include "DHT.h"

// https://os.mbed.com/users/Wimpie/co/DHT
DHT sensor(A0, SEN11301P); // sensor = SEN11301P

int main()
{
    int error;
    printf("\r\n=============================================\r\n");
    thread_sleep_for(1000);
    while(true) {
        error = sensor.readData();
        printf("%d", error);
        if(error == 0) {
            printf("Temperature:\t%4.2f C, %4.2f F, %4.2f K\r\n", sensor.ReadTemperature(CELCIUS),
               sensor.ReadTemperature(FARENHEIT), sensor.ReadTemperature(KELVIN));
            printf("Humidity:\t%4.2f%%\r\n", sensor.ReadHumidity());
            printf("=============================================\r\n");
            thread_sleep_for(5000);
        } else {
            thread_sleep_for(1000);
            }
    }
}