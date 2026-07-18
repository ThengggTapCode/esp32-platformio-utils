#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <time.h>
#include "wifi_connection.h"
#include "ntp_clock.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

void NTPClock::clockUpdate() {
    if (timeClient.update()) Serial0.println("[NTPClient] Update successful!");
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((const time_t *)&epochTime);
    
    this->dayOfMonth = ptm->tm_mday;
    this->dayOfWeek = ptm->tm_wday + 1;
    this->month = ptm->tm_mon + 1;
    this->year = ptm->tm_year + 1900;
    this->hour = timeClient.getHours();
    this->minute = timeClient.getMinutes();
    this->second = timeClient.getSeconds();
}

void NTPClock::clockForceUpdate() { timeClient.forceUpdate(); }

void NTPClock::setup() {
    WiFi_Connection wifi = WiFi_Connection(15);
    while (true) {
        wifi.connect();
        if (wifi.isConnected()) break;
    }
    timeClient.begin();
    clockForceUpdate();
}

String NTPClock::formatUInt8Type(uint8_t data) {
    if (data >= 10) return String(data);
    return "0" + String(data);
}

String NTPClock::getDayOfWeek(bool shortDate, bool longDate) {
    if (shortDate && longDate)
    return "[ERROR] Cannot choose both short date and long date!";
    if (!shortDate && !longDate)
    return "[ERROR] Please choose at least one and only one format!";
    
    uint8_t index = this->dayOfWeek - 1;
    if (index < 0 || index > 6) return "[ERROR] Invalid day in week!";

    if (shortDate) {
        const char* days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return String(days[index]);
    }
    const char* days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return String(days[index]);
}

String NTPClock::getDayOfMonth() { return formatUInt8Type(this->dayOfMonth); }
String NTPClock::getMonth() { return formatUInt8Type(this->month); }
String NTPClock::getYear() { return String(this->year).c_str(); }
String NTPClock::getHour() { return formatUInt8Type(this->hour); }
String NTPClock::getMinute() { return formatUInt8Type(this->minute); }
String NTPClock::getSecond() { return formatUInt8Type(this->second); }


NTPClock::NTPClock() {
    this->dayOfMonth = 0;
    this->dayOfWeek = 0;
    this->month = 0;
    this->year = 0;
    this->hour = 0;
    this->minute = 0;
    this->second = 0;
}