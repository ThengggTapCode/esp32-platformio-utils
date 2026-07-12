#pragma once
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

constexpr uint8_t SDA_I2C = 8, SCL_I2C = 9,
                    DISPLAY_WIDTH = 128, DISPLAY_HEIGHT = 64;
extern Adafruit_SH1106G display;
extern bool displayIsSetUp;

void displaySetup();