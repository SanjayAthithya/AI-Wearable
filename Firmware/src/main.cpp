#include <Arduino.h>
#include "imu.h"

void setup()
{
    Serial.begin(115200);

    while (!Serial);

    Serial.println();
    Serial.println("================================");
    Serial.println("AI Wearable Project");
    Serial.println("Initializing MPU6500...");
    Serial.println("================================");

    if (!imuBegin())
    {
        Serial.println("MPU6500 Initialization Failed");

        while (1);
    }

    Serial.println("MPU6500 Ready");

    imuCalibrate();
}

void loop()
{
    imuUpdate();

    imuPrint();

    delay(500);
}