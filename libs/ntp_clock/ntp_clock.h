#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "wifi_connection.h"

#define NTP_OFFSET 7*3600 // GMT+7
#define NTP_INTERVAL 60*1000 // updates after 60s
#define NTP_ADDRESS "pool.ntp.org" // NTP server address

extern NTPClient timeClient;
void ntpClockSetup();