#include "imu.h"
#include <Wire.h>

#define MPU_ADDR 0x68

//==================================================
// Raw Sensor Data
//==================================================

int16_t rawAccX, rawAccY, rawAccZ;
int16_t rawGyroX, rawGyroY, rawGyroZ;
int16_t rawTemp;

//==================================================
// Converted Data
//==================================================

IMUData imuData;

//==================================================
// Gyroscope Offsets
//==================================================

float gyroOffsetX = 0;
float gyroOffsetY = 0;
float gyroOffsetZ = 0;

//==================================================
// Write Register
//==================================================

void writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

//==================================================
// Read Register
//==================================================

uint8_t readRegister(uint8_t reg)
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom((uint8_t)MPU_ADDR, (uint8_t)1);

    if (Wire.available())
        return Wire.read();

    return 0xFF;
}

//==================================================
// Initialize MPU6500
//==================================================

bool imuBegin()
{
    Wire.begin(21, 22);

    Wire.beginTransmission(MPU_ADDR);

    if (Wire.endTransmission() != 0)
        return false;

    // Wake sensor
    writeRegister(0x6B, 0x00);

    delay(100);

    // DLPF = 20Hz
    writeRegister(0x1A, 0x04);

    // Gyroscope ±250 dps
    writeRegister(0x1B, 0x00);

    // Accelerometer ±2g
    writeRegister(0x1C, 0x00);

    return (readRegister(0x75) == 0x70);
}

//==================================================
// Read Raw Data
//==================================================

void imuReadRaw()
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);

    Wire.requestFrom((uint8_t)MPU_ADDR, (uint8_t)14);

    if (Wire.available() == 14)
    {
        rawAccX = (Wire.read() << 8) | Wire.read();
        rawAccY = (Wire.read() << 8) | Wire.read();
        rawAccZ = (Wire.read() << 8) | Wire.read();

        rawTemp = (Wire.read() << 8) | Wire.read();

        rawGyroX = (Wire.read() << 8) | Wire.read();
        rawGyroY = (Wire.read() << 8) | Wire.read();
        rawGyroZ = (Wire.read() << 8) | Wire.read();
    }
}

//==================================================
// Gyroscope Calibration
//==================================================

void imuCalibrate()
{
    const int samples = 1000;

    long gx = 0;
    long gy = 0;
    long gz = 0;

    Serial.println();
    Serial.println("================================");
    Serial.println("Calibrating Gyroscope...");
    Serial.println("Keep sensor completely still");
    Serial.println("================================");

    for (int i = 0; i < samples; i++)
    {
        imuReadRaw();

        gx += rawGyroX;
        gy += rawGyroY;
        gz += rawGyroZ;

        delay(2);
    }

    gyroOffsetX = gx / (float)samples;
    gyroOffsetY = gy / (float)samples;
    gyroOffsetZ = gz / (float)samples;

    Serial.println("Calibration Complete");
    Serial.println();
}

//==================================================
// Convert Engineering Units
//==================================================

void imuConvert()
{
    // Accelerometer (DO NOT remove gravity)

    imuData.accX = rawAccX / 16384.0f;
    imuData.accY = rawAccY / 16384.0f;
    imuData.accZ = rawAccZ / 16384.0f;

    // Gyroscope

    imuData.gyroX = (rawGyroX - gyroOffsetX) / 131.0f;
    imuData.gyroY = (rawGyroY - gyroOffsetY) / 131.0f;
    imuData.gyroZ = (rawGyroZ - gyroOffsetZ) / 131.0f;

    // Temperature

    imuData.temperature = (rawTemp / 333.87f) + 21.0f;
}

//==================================================
// Update
//==================================================

void imuUpdate()
{
    imuReadRaw();
    imuConvert();
}

//==================================================
// Print
//==================================================

void imuPrint()
{
    Serial.println("==============================");

    Serial.print("ACC : ");
    Serial.print(imuData.accX, 3);
    Serial.print("  ");
    Serial.print(imuData.accY, 3);
    Serial.print("  ");
    Serial.println(imuData.accZ, 3);

    Serial.print("GYRO: ");
    Serial.print(imuData.gyroX, 2);
    Serial.print("  ");
    Serial.print(imuData.gyroY, 2);
    Serial.print("  ");
    Serial.println(imuData.gyroZ, 2);

    Serial.print("TEMP: ");
    Serial.print(imuData.temperature, 2);
    Serial.println(" C");

    Serial.println();
}

//==================================================
// Return Data
//==================================================

IMUData getIMUData()
{
    return imuData;
}