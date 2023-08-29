#include "mbed.h"
#include "ESP-call.h"
#include "LM75B.h"
PwmOut led_r(PTA2);

NodeMCU_PGM http_server_l[] = {
    "", 1,
    "wifi.setmode(wifi.STATION)", 1,
    "", 1,
    "station_cfg={}", 1,
    "station_cfg.ssid=\"free\"", 1,
    "station_cfg.pwd=\"12345678\"", 1,
    "station_cfg.save=false", 1,
    "wifi.sta.config(station_cfg)", 1,
    "", 1,
    "wifi.sta.connect()", 80, 
    "", 1,
    "print(wifi.sta.status())", 1,
    "print(wifi.sta.getip())", 1,
    "", 1,
    "Red=\"checked\"", 1,
    "_Red=\"\"", 1,
    "uptime=0", 1,
    "http_resp = \"HTTP/1.0 200 OK\\r\\nContent-Type: text/html\\r\\n\\r\\n\"",1,
    "html_main1 = \"<h1>Hello, NodeMCU!</h1>\"",1,
    "html_main2 = \"<form id=\\\"new\\\" method=\\\"POST\\\">\"", 1,
    "html_main3 = \"<h1>LED \"",1,
    "html_main4 = \"on<input type=\\\"radio\\\" name=\\\"LED_R\\\" value=\\\"on\\\" %s>\"",1,
    "html_main5 = \"off<input type=\\\"radio\\\" name=\\\"LED_R\\\" value=\\\"off\\\" %s>\"",1,
    "html_main6 = \"<input type=\\\"submit\\\" value=\\\"Submit\\\"></h1>\"",1,
    "html_main7 = \"<h1>Bye!</h1>\"",1,
    "html_main8 = \"</form>\"", 1,
    "srv = net.createServer(net.TCP)",1,
    "srv:listen(80, function(conn)",1,
    "conn:on(\"receive\", function(sck, payload)",1,
    "if string.match(payload, \"LED_R=off\")", 1,
    "then print(\"^1\") Red=\"\" _Red=\"checked\" end", 1,
    "if string.match(payload, \"LED_R=on\")", 1,
    "then print(\"^0\") Red=\"checked\" _Red=\"\" end", 1,
    "print(payload)",1,
    "sck:send(http_resp)",1,
    "sck:send(html_main1)",1,
    "sck:send(html_main2)",1,
    "sck:send(html_main3)",1,
    "sck:send(string.format(html_main4, Red))",1,
    "sck:send(string.format(html_main5, _Red))",1,
    "sck:send(html_main6)",1,
    "sck:send(html_main7)",1,
    "sck:send(html_main8)",1,
    "end)",1,
    "conn:on(\"sent\", function(sck) sck:close() end)",1,
    "end)",1,
    NULL, 0, 
};
int main()
{
    PC.baud(115200);
    ESP.baud(115200);
    led_r = 0;
    PC.printf("\r\nReset ESP...\r\n");
    ESP_reset();
    PC.printf("Setup ESP noecho...\r\n");
    ESP_noecho();
    PC.printf("Execute a NodeMCU program...\r\n");
    ESP_call_multi(http_server_l);
    PC.printf("\r\nESP receive mode...\r\n");
    ESP.attach(&ISR_ESP_to_PC, Serial::RxIrq);
    while(1) {
        led_r = LED_status;
    }
}
