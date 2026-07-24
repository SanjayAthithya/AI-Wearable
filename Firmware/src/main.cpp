#include <Arduino.h>

#include "imu.h"
#include "oled.h"

void setup()
{
    Serial.begin(115200);

    while (!Serial);

    Serial.println();
    Serial.println("================================");
    Serial.println("AI Wearable Project");
    Serial.println("System Initializing...");
    Serial.println("================================");

    // Initialize OLED
    if (!oledBegin())
    {
        Serial.println("OLED Initialization Failed");

        while (1);
    }

    oledShowBoot();

    delay(2000);

    // Initialize MPU6500
    if (!imuBegin())
    {
        Serial.println("MPU6500 Initialization Failed");

        oledShowAlert("MPU6500 ERROR");

        while (1);
    }

    Serial.println("MPU6500 Ready");

    imuCalibrate();

    delay(1000);
}

void loop()
{
    imuUpdate();

    IMUData imu = getIMUData();

    // Show live MPU6500 values on OLED
    oledShowMotion(
        imu.accX,
        imu.accY,
        imu.accZ,
        imu.gyroX,
        imu.gyroY,
        imu.gyroZ);

    // Debug output on Serial Monitor
    imuPrint();

    delay(100);
}