#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <time.h>
#include "wifi_connection.h"

#define NTP_OFFSET 7*3600 // GMT+7
#define NTP_INTERVAL 60*1000 // updates after 60s
#define NTP_ADDRESS "pool.ntp.org" // NTP server address

extern NTPClient timeClient;

class NTPClock {
private:
    uint8_t dayOfWeek, dayOfMonth, month;
    uint8_t hour, minute, second;
    int year;
    String formatUInt8Type(uint8_t data);
    void clockForceUpdate();
    
public:
    NTPClock();
    void setup();
    void clockUpdate();
    String getDayOfWeek(bool shortDate, bool longDate);
    String getDayOfMonth();
    String getMonth();
    String getYear();
    String getHour();
    String getMinute();
    String getSecond();
};