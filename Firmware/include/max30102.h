#ifndef MAX30102_H
#define MAX30102_H

#include <Arduino.h>

//=========================================
// MAX30102 Sensor Data
//=========================================

struct MAX30102Data
{
    uint32_t ir;
    uint32_t red;

    float heartRate;
    float spo2;
};

//=========================================
// Driver Functions
//=========================================

// Initialize MAX30102
bool maxBegin();

// Read raw FIFO values
void maxReadRaw();

// Update sensor data
void maxUpdate();

// Print sensor data
void maxPrint();

// Return latest sensor data
MAX30102Data getMAXData();

#endif