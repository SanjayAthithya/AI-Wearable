#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

struct IMUData
{
    float accX;
    float accY;
    float accZ;

    float gyroX;
    float gyroY;
    float gyroZ;

    float temperature;
};

bool imuBegin();

void imuCalibrate();

void imuReadRaw();

void imuConvert();

void imuUpdate();

void imuPrint();

IMUData getIMUData();

#endif