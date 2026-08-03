#ifndef COMM_H
#define COMM_H

#include <Arduino.h>

bool commBegin();

void commSend(const String &data);

bool commConnected();

#endif