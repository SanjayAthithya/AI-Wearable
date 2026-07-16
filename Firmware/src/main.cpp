#include <Arduino.h>
#include "imu.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);
    if(imuBegin())
    {
        Serial.println("MPU6500 Driver Ready");
    }
    else
    {
        Serial.println("MPU6500 Initialization Failed");
        while(true);
    }
}
void loop()
{
    imuRead();
    imuPrint();
    delay(500);
}