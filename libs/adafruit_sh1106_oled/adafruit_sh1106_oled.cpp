#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "adafruit_sh1106_oled.h"

Adafruit_SH1106G display = Adafruit_SH1106G(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);
bool displayIsSetUp = false;

void displaySetup() {
    Wire.begin(SDA_I2C, SCL_I2C);
    while (!display.begin(0x3C, true));
    displayIsSetUp = true;
    display.setTextColor(SH110X_WHITE);
    display.clearDisplay();
    display.display();
}