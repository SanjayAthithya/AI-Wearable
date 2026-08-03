#include "serial_stream.h"

bool serialBegin(uint32_t baudRate)
{
    Serial.begin(baudRate);

    delay(1000);

    return true;
}

void serialSend(const String &data)
{
    Serial.println(data);
}

bool serialConnected()
{
    return true;
}