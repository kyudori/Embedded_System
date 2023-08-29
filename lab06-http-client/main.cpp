#include "mbed.h"
#include "ESP-call.h"

// NodeMCU program

NodeMCU_PGM http_client[] = {
    "", 1,
    "wifi.setmode(wifi.STATION)", 1,
    "", 1,
    "station_cfg={}", 1,
    "station_cfg.ssid=\"SSID\"", 1,
    "station_cfg.pwd=\"PASSWORD\"", 1,
    "station_cfg.save=false", 1,
    "wifi.sta.config(station_cfg)", 1,
    "", 1,
    "wifi.sta.connect()", 80, // long delay here!
    "", 1,
    "print(wifi.sta.status())", 1,
    "print(wifi.sta.getip())", 1,
    "", 1,
    "socket=net.createConnection(net.TCP, 0)", 1,
    "socket:on(\"receive\", function(sck, c) print(c) end)", 1,
    "socket:connect(80,\"wifitest.adafruit.com\")", 1,
    "socket:send(\"GET /testwifi/index.html HTTP/1.1\\r\\nHost:wifitest.adafruit.com\\r\\nConnection: keepalive\\r\\nAccept: */*\\r\\n\\r\\n\")",
    50, // long delay here!
    NULL, 0, // last line should be NULL and 0
};