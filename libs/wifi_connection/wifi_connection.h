#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Preferences.h>
#include "input_buffer.h"

extern Preferences pref;

class WiFi_Connection {
private:
    String ssid;
    String password;
    bool foundSavedSSID();
    void saveSSID();
    void getInfo();
    void connectionAttempt();
public:
    WiFi_Connection();
    void connect();
    void disconnect();
    void forget();
    bool isConnected();
};