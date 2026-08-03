#include <Arduino.h>
#include <Wire.h>
#include "comm.h"
#include "imu.h"
#include "hr_module.h"
#include "oled.h"
#include "csv_logger.h"

//==================================================
// Debug Output
//==================================================
// 1 = Human-readable serial output
// 0 = CSV-only output (recommended when logging)
#define DEBUG_SERIAL 0

//==================================================
// Setup
//==================================================

void setup()
{
    //--------------------------------------------------
    // Communication
    //--------------------------------------------------

    commBegin();
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

    //--------------------------------------------------
    // CSV Header
    //--------------------------------------------------

    csvPrintHeader();
}

//==================================================
// Main Loop
//==================================================

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
    // CSV Logger
    //--------------------------------------------------

    csvLog();

#if DEBUG_SERIAL

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

#endif

    //--------------------------------------------------
    // Sampling Rate
    //--------------------------------------------------

    delay(20);
}