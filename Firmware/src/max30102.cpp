#include "max30102.h"
#include <Wire.h>

//=========================================
// Sensor Data
//=========================================

MAX30102Data maxData;

//=========================================
// Initialize MAX30102
//=========================================

bool maxBegin()
{
    // Implementation will be added in Task 4

    return true;
}

//=========================================
// Read Raw Sensor Data
//=========================================

void maxReadRaw()
{
    // Read FIFO registers
    // (Task 4)
}

//=========================================
// Update Sensor
//=========================================

void maxUpdate()
{
    maxReadRaw();

    // Future:
    // Calculate Heart Rate
    // Calculate SpO2
}

//=========================================
// Print Sensor Data
//=========================================

void maxPrint()
{
    Serial.println("==============================");

    Serial.print("IR   : ");
    Serial.println(maxData.ir);

    Serial.print("RED  : ");
    Serial.println(maxData.red);

    Serial.print("HR   : ");
    Serial.print(maxData.heartRate);
    Serial.println(" bpm");

    Serial.print("SpO2 : ");
    Serial.print(maxData.spo2);
    Serial.println(" %");

    Serial.println("==============================");
    Serial.println();
}

//=========================================
// Return Data
//=========================================

MAX30102Data getMAXData()
{
    return maxData;
}