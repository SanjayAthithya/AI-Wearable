#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <U8g2lib.h>

#include "imu.h"
#include "hr_module.h"

//==================================================
// Initialization
//==================================================

bool oledBegin();

//==================================================
// Display Functions
//==================================================

void oledSplash();

void oledUpdate();

//==================================================
// Individual Pages
//==================================================

void oledHeartPage();

void oledAccelPage();

void oledGyroPage();

void oledTempPage();

//==================================================
// Page Control
//==================================================

void oledNextPage();

#endif