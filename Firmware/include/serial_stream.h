#ifndef SERIAL_STREAM_H
#define SERIAL_STREAM_H

#include <Arduino.h>

bool serialBegin(uint32_t baudRate = 115200);

void serialSend(const String &data);

bool serialConnected();

#endif