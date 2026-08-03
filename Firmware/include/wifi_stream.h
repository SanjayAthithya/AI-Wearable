#ifndef WIFI_STREAM_H
#define WIFI_STREAM_H

#include <Arduino.h>

bool wifiBegin();

bool wifiConnectServer();      // <-- Add this

void wifiSend(const String &data);

bool wifiConnected();

#endif