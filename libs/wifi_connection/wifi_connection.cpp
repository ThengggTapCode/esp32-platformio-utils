#include <Arduino.h>
#include <WiFi.h>
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
    Serial.print("[WiFi] Enter SSID: ");
    this->ssid = inputBuffer();
    Serial.print("[WiFi] Enter password: ");
    this->password = inputBuffer(false, true);
}
bool WiFi_Connection::foundSavedSSID() {
    pref.begin("wifi_config", true);
    String savedSSID = "", savedPassword = "";

    if (pref.isKey("ssid"))
        savedSSID = pref.getString("ssid", "");
    if (pref.isKey("password"))
        savedPassword = pref.getString("password", "");
    pref.end();

    if (savedSSID != "" && savedPassword != "") {
        this->ssid = savedSSID;
        this->password = savedPassword;
        return true;
    }
    return false;
}
void WiFi_Connection::connectionAttempt() {
    Serial.printf("[WiFi] Connecting to %s", this->ssid.c_str());
    uint8_t connectingTime = 0;
    WiFi.begin(this->ssid.c_str(), this->password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
        connectingTime += 1;

        if (connectingTime >= this->timeOutSecond) {
            Serial.println("\n[WiFi] Connection timeout! Your SSID might be unavailable at the moment, or your input was incorrect.");
            return;
        }
    }
    Serial.printf("\n[WiFi] Successfully connected to %s.\n", this->ssid.c_str());
    saveSSID();
}
void WiFi_Connection::connect() {
    if (foundSavedSSID()) {
        Serial.printf("[WiFi] Found recently saved SSID: %s.\n", this->ssid.c_str());
        while (true) {
            Serial.print("Proceed to connect? [Y/n] ");
            String yn = inputBuffer(true, false);
            yn.toLowerCase();

            if (yn == "y" || yn == "") {
                connectionAttempt();
                if (isConnected())
                    return;
                break;
            }
            else if (yn == "n")
                break;
            else 
                Serial.println("\nPlease try again with a valid input");
        }
    }
    getInfo();
    connectionAttempt();
}
void WiFi_Connection::disconnect() {
    WiFi.disconnect();
    Serial.println("[WiFi] Disconnected.");
}
void WiFi_Connection::forget() {
    WiFi.disconnect(true, true);
    pref.begin("wifi_config", false);
    pref.clear();
    pref.end();
    this->ssid = "";
    this->password = "";
    Serial.println("[WiFi] SSID was forgot.");
}
WiFi_Connection::WiFi_Connection(uint8_t timeOutSecond) {
    this->ssid = "";
    this->password = "";
    this->timeOutSecond = timeOutSecond;
}