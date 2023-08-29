#include "mbed.h"
#include "ESP-call.h"
#include "LM75B.h"
#include "DHT.h"
#include "C12832.h"
#include <string>

//thread
Thread th1, th2, th3;

//mutex
Mutex mutex;

Ticker ticker; // A 1.0 sec ticker

//sensor info
float cel = 0.0;
float hum = 0.0;

//timer offset
long offset = 0;
Timer timer;



//temp&hum
DHT hum_sensor(A0, SEN11301P);

//lcd
C12832 lcd(D11, D13, D12, D7, D10);

//joystick
InterruptIn sw2(SW2); // sw2 = SW2
InterruptIn sw3(SW3);
InterruptIn up(A2); // up = A1
InterruptIn down(A3);
InterruptIn left(A4);
InterruptIn rite(A5);
InterruptIn center(D4);

//buzzer
PwmOut buzzer(D6);
DigitalOut fan(D8);

//led
DigitalOut led_r(D5);

NodeMCU_PGM http_server[] = {
    "", 1,
    "wifi.setmode(wifi.STATION)",1,
    "", 1,
    "station_cfg={}", 1,
    "station_cfg.ssid=\"free\"", 1,
    "station_cfg.pwd=\"12345678\"", 1,
    "station_cfg.save=false", 1,
    "wifi.sta.config(station_cfg)", 1,
    "", 1,
    "wifi.sta.connect()", 1,
    "", 1,
    "print(wifi.sta.status())", 1,
    "print(wifi.sta.getip())", 1,
    "", 1,
    "Red=\"checked\"", 1,
    "_Red=\"\"", 1,
    "hum=0.0", 1,
    "cel=0.0", 1,
    "http_resp = \"HTTP/1.0 200 OK\\r\\nContent-Type: text/html\\r\\n\\r\\n\"", 1,
    "html_main1 = \"<h1>Hello</h1>\"", 1,
    "html_main2 = \"<h1>Temperature(C): %5.2f</h1>\"", 1,
    "html_main3 = \"<h1>Humidity(%%): %5.2f</h1>\"", 1,
    "html_main4 = \"<form id=\\\"new\\\" method=\\\"POST\\\">\"", 1,
    "html_main5 = \"<h1>LED \"",1,
    "html_main6 = \"on<input type=\\\"radio\\\" name=\\\"LED_R\\\" value=\\\"on\\\" %s>\"",1,
    "html_main7 = \"off<input type=\\\"radio\\\" name=\\\"LED_R\\\" value=\\\"off\\\" %s>\"",1,
    "html_main8 = \"<input type=\\\"submit\\\" value=\\\"Submit\\\"></h1>\"",1,
    "html_main9 = \"</form>\"", 1,
    "", 1,
    "srv = net.createServer(net.TCP)", 1,
    "srv:listen(80, function(conn)", 1,
    "   conn:on(\"receive\", function(sck, payload)", 1,
    "       if string.match(payload, \"LED_R=off\")", 1,
    "       then print(\"^0\") Red=\"\" _Red=\"checked\" end", 1,
    "       if string.match(payload, \"LED_R=on\")", 1,
    "       then print(\"^1\") Red=\"checked\" _Red=\"\" end", 1,        
    "       print(payload)", 1,
    "       sck:send(http_resp)", 1,
    "       sck:send(html_main1)", 1,
    "       sck:send(string.format(html_main2, cel))", 1,
    "       sck:send(string.format(html_main3, hum))", 1,
    "       sck:send(html_main4)", 1,
    "       sck:send(html_main5)", 1,
    "       sck:send(string.format(html_main6, Red))", 1,
    "       sck:send(string.format(html_main7, _Red))", 1,
    "       sck:send(html_main8)", 1,
    "       sck:send(html_main9)", 1,
    "       end)", 1,
    "   conn:on(\"sent\", function(sck) sck:close() end)", 1,
    "end)", 1,
    NULL, 0,
};

// Callback function that sends uptime to ESP

void callback_send_uptime(void)
{
    ESP.printf("cel=%5.2f\r\n", cel);
    ESP.printf("hum=%5.2f\r\n", hum);    
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

//light thread
void thread_light(){
    while(true){
        mutex.lock();
        led_r = LED_status;
        mutex.unlock();
    }

}


//clock thread
void thread_clock(){

    long time;
    unsigned char h,m,s,ms;

    up.rise(&ISR_up);
    down.rise(&ISR_down);
    left.rise(&ISR_left);
    rite.rise(&ISR_rite);
    center.rise(&ISR_center);

    lcd.cls();
    lcd.locate(0,6);
    lcd.printf("Digital Clock!");

    while(true){
        mutex.lock();
        time = timer.read_ms();
        if((time + offset) < 0) offset = (-1)*time;
        time = time + offset;

        s = (time / 1000) % 60;
        m = ((time / 1000) / 60) % 60;
        h = ((time / 1000) / (60*60)) % 24;
        lcd.locate(0, 16);
        lcd.printf("Current Time: %02d:%02d:%02d", h, m, s);

        thread_sleep_for(10);
        if(m == 0 && s<3){
            buzzer.period(1.0/440);
            buzzer = 0.5;
            thread_sleep_for(1000);
            buzzer = 0.0;
        }
        mutex.unlock();
    }
}


void thread_read(){
    int error;
    while(true){
        mutex.lock();
        cel = hum_sensor.ReadTemperature(CELCIUS);
        error = hum_sensor.readData();
        if(error == 0){
            hum = hum_sensor.ReadHumidity();
            thread_sleep_for(5000);
        }
        else thread_sleep_for(1000);    
        mutex.unlock();    
    }
}


int main()
{
    // Config baudrate of PC and ESP
    PC.baud(115200);
    ESP.baud(115200);
    
    // Reset ESP
    PC.printf("\r\nReset ESP...\r\n");
    ESP_reset();

    // Setup ESP noecho mode
    PC.printf("Setup ESP noecho...\r\n");
    ESP_noecho();
    
    // Execute a NodeMCU program
    PC.printf("Execute a NodeMCU program...\r\n");
    ESP_call_multi(http_server);

    // Config ESP to PC receive mode
    PC.printf("\r\nESP receive mode...\r\n");
    ESP.attach(&ISR_ESP_to_PC, Serial::RxIrq);

    // Attach 1.0 sec ticker callback function
    ticker.attach(&callback_send_uptime, 1.0);

    timer.start();


    th1.start(thread_clock);
    th2.start(thread_light);
    th3.start(thread_read);

    
    // Main thread sleeps
    while(1) {   
    }
}