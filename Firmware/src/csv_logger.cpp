#include "csv_logger.h"

#include "imu.h"
#include "hr_module.h"

void csvPrintHeader()
{
    Serial.println(
        "Time,IR,RED,Finger,BPM,SpO2,"
        "AccX,AccY,AccZ,"
        "GyroX,GyroY,GyroZ,"
        "Temp");
}

void csvLog()
{
    IMUData imu = getIMUData();

    Serial.print(millis());
    Serial.print(",");

    Serial.print(getIRValue());
    Serial.print(",");

    Serial.print(getRedValue());
    Serial.print(",");

    Serial.print(fingerDetected());
    Serial.print(",");

    if (bpmValid())
        Serial.print(getBPM());
    else
        Serial.print(-1);

    Serial.print(",");

    if (spo2Valid())
        Serial.print(getSpO2());
    else
        Serial.print(-1);

    Serial.print(",");

    Serial.print(imu.accX, 4);
    Serial.print(",");

    Serial.print(imu.accY, 4);
    Serial.print(",");

    Serial.print(imu.accZ, 4);
    Serial.print(",");

    Serial.print(imu.gyroX, 4);
    Serial.print(",");

    Serial.print(imu.gyroY, 4);
    Serial.print(",");

    Serial.print(imu.gyroZ, 4);
    Serial.print(",");

    Serial.println(imu.temperature, 2);
}