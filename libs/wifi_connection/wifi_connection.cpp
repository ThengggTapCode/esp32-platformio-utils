#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Preferences.h>
#include "input_buffer.h"
#include "wifi_connection.h"

Preferences pref;

bool WiFi_Connection::isConnected() { return WiFi.status() == WL_CONNECTED; }

void WiFi_Connection::saveSSID() {
    pref.begin("wifi_config", false);
    pref.putString("ssid", this->ssid);
    pref.putString("password", this->password);
    pref.end();
}
void WiFi_Connection::getInfo() {
    Serial0.print("[WiFi] Enter SSID: ");
    this->ssid = inputBuffer();
    Serial0.print("[WiFi] Enter password: ");
    this->password = inputBuffer(true);
}
bool WiFi_Connection::foundSavedSSID() {
    pref.begin("wifi_config", true);
    String savedSSID = pref.getString("ssid", "");
    String savePassword = pref.getString("password", "");
    pref.end();

    if (savedSSID != "") {
        this->ssid = savedSSID;
        this->password = savePassword;
        return true;
    }
    return false;
}
void WiFi_Connection::connectionAttempt() {
    Serial0.printf("[WiFi] Connecting to %s", this->ssid.c_str());
    uint8_t connectingTime = 0;
    WiFi.begin(this->ssid.c_str(), this->password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial0.print(".");
        connectingTime += 1;

        if (connectingTime >= 30) {
            Serial0.println("[WiFi] Connection timeout. Please retry");
            return;
        }
    }
    Serial0.printf("\n[WiFi] Successfully connected to %s\n", this->ssid.c_str());
    saveSSID();
}
void WiFi_Connection::connect() {
    if (foundSavedSSID())
        Serial0.printf("[WiFi] Found saved SSID: %s\n", this->ssid.c_str());
    else
        getInfo();

    connectionAttempt();
}
void WiFi_Connection::disconnect() {
    WiFi.disconnect();
    Serial0.println("[WiFi] Disconnected");
}
void WiFi_Connection::forget() {
    WiFi.disconnect(true, true);
    pref.begin("wifi_config", false);
    pref.clear();
    pref.end();
    this->ssid = "";
    this->password = "";
    Serial0.println("[WiFi] SSID was forgot");
}
WiFi_Connection::WiFi_Connection() {
    this->ssid = "";
    this->password = "";
}