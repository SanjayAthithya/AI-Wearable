#pragma once

#include <Arduino.h>

bool heartRateBegin();
void heartRateUpdate();

bool fingerDetected();

long getIRValue();
long getRedValue();

int getBPM();
int getSpO2();

bool bpmValid();
bool spo2Valid();