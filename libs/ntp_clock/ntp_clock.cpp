#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "wifi_connection.h"
#include "ntp_clock.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

void ntpClockSetup() {
    WiFi_Connection wifi = WiFi_Connection(15);
    while (true) {
        wifi.connect();
        if (wifi.isConnected()) break;
    }
    timeClient.begin();
}