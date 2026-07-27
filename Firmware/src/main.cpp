#include <Arduino.h>
#include <Wire.h>

#include "imu.h"
#include "hr_module.h"
#include "oled.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("=================================");
    Serial.println("      AI Wearable Starting");
    Serial.println("=================================");

    //--------------------------------------------------
    // Shared I2C Bus
    //--------------------------------------------------

    Wire.begin(21, 22);

    //--------------------------------------------------
    // OLED
    //--------------------------------------------------

    if (!oledBegin())
    {
        Serial.println("OLED Initialization Failed!");

        while (1);
    }

    //--------------------------------------------------
    // MPU6500
    //--------------------------------------------------

    Serial.print("Initializing MPU6500... ");

    if (!imuBegin())
    {
        Serial.println("FAILED");

        while (1);
    }

    Serial.println("OK");

    imuCalibrate();

    //--------------------------------------------------
    // MAX30102
    //--------------------------------------------------

    Serial.print("Initializing MAX30102... ");

    if (!heartRateBegin())
    {
        Serial.println("FAILED");

        while (1);
    }

    Serial.println("OK");

    Serial.println();
    Serial.println("System Ready");
}

void loop()
{
    //--------------------------------------------------
    // Update Sensors
    //--------------------------------------------------

    imuUpdate();

    heartRateUpdate();

    //--------------------------------------------------
    // Update OLED
    //--------------------------------------------------

    oledUpdate();

    //--------------------------------------------------
    // Serial Debug (Optional)
    //--------------------------------------------------

    static unsigned long lastPrint = 0;

    if (millis() - lastPrint >= 500)
    {
        lastPrint = millis();

        IMUData imu = getIMUData();

        Serial.println("--------------------------------");

        Serial.print("IR : ");
        Serial.print(getIRValue());

        Serial.print("   RED : ");
        Serial.print(getRedValue());

        Serial.print("   Finger : ");
        Serial.println(fingerDetected());

        Serial.print("ACC : ");
        Serial.print(imu.accX, 3);
        Serial.print("  ");
        Serial.print(imu.accY, 3);
        Serial.print("  ");
        Serial.println(imu.accZ, 3);

        Serial.print("GYRO : ");
        Serial.print(imu.gyroX, 2);
        Serial.print("  ");
        Serial.print(imu.gyroY, 2);
        Serial.print("  ");
        Serial.println(imu.gyroZ, 2);

        Serial.print("TEMP : ");
        Serial.print(imu.temperature, 2);
        Serial.println(" C");

        Serial.println();
    }
}