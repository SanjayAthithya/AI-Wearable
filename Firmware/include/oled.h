#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

//======================================
// Initialization
//======================================

bool oledBegin();

//======================================
// Basic Functions
//======================================

void oledClear();

//======================================
// Screens
//======================================

void oledShowBoot();

void oledShowHealth(
    int heartRate,
    int spo2,
    float temperature,
    float battery);

void oledShowMotion(
    float accX,
    float accY,
    float accZ,
    float gyroX,
    float gyroY,
    float gyroZ);

void oledShowAlert(
    const String &message);

void oledShowDebug(
    uint32_t ir,
    uint32_t red,
    bool wifiStatus);

#endif