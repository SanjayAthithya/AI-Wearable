#include "imu.h"
#include <Wire.h>
#define MPU_ADDR 0x68
int16_t AccX, AccY, AccZ;
int16_t Temp;
int16_t GyroX, GyroY, GyroZ;

bool imuBegin()
{
    Wire.begin(21,22);

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B);
    Wire.write(0x00);

    if(Wire.endTransmission()!=0)
        return false;

    return true;
}
void imuRead()
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);

    Wire.requestFrom(MPU_ADDR,14);

    if(Wire.available()==14)
    {
        AccX=(Wire.read()<<8)|Wire.read();
        AccY=(Wire.read()<<8)|Wire.read();
        AccZ=(Wire.read()<<8)|Wire.read();

        Temp=(Wire.read()<<8)|Wire.read();

        GyroX=(Wire.read()<<8)|Wire.read();
        GyroY=(Wire.read()<<8)|Wire.read();
        GyroZ=(Wire.read()<<8)|Wire.read();
    }
}
void imuPrint()
{
    Serial.print("ACC: ");
    Serial.print(AccX);
    Serial.print(" ");
    Serial.print(AccY);
    Serial.print(" ");
    Serial.println(AccZ);
    Serial.print("GYRO: ");
    Serial.print(GyroX);
    Serial.print(" ");
    Serial.print(GyroY);
    Serial.print(" ");
    Serial.println(GyroZ);
    Serial.print("TEMP: ");
    Serial.println(Temp);
    Serial.println("-------------------------");
}