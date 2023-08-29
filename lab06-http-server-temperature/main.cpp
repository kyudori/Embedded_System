#include "mbed.h"
#include "ESP-call.h"
#include "LM75B.h"

Ticker ticker; // A 1.0 sec ticker
uint64_t uptime = 0; // Current uptime
float cel = 0.0;
LM75B temp(D14, D15);

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
    "uptime=0", 1,
    "cel=0.0", 1,
    "http_resp = \"HTTP/1.0 200 OK\\r\\nContent-Type: text/html\\r\\n\\r\\n\"", 1,
    "html_main1 = \"<h1>Hello, NodeMCU!</h1>\"", 1,
    "html_main2 = \"<h1>Temperature(C): %5.2f</h1>\"", 1,
    "html_main3 = \"<h1>Uptime(secs): %d</h1>\"", 1,
    "html_main4 = \"<h1>Bye!</h1>\"", 1,
    "", 1,
    "srv = net.createServer(net.TCP)", 1,
    "srv:listen(80, function(conn)", 1,
    "   conn:on(\"receive\", function(sck, payload)", 1,        
    "       print(payload)", 1,
    "       sck:send(http_resp)", 1,
    "       sck:send(html_main1)", 1,
    "       sck:send(string.format(html_main2, cel))", 1,
    "       sck:send(string.format(html_main3, uptime))", 1,
    "       sck:send(html_main4)", 1,
    "       end)", 1,
    "   conn:on(\"sent\", function(sck) sck:close() end)", 1,
    "end)", 1,
    NULL, 0,
};

// Callback function that sends uptime to ESP

void callback_send_uptime(void)
{
    uptime = uptime + 1;
    ESP.printf("cel=%5.2f\r\n", cel);
    ESP.printf("uptime=%llu\r\n", uptime);
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

    
    // Main thread sleeps
    while(1) {
        cel = temp.read();
    }
}