#include "hr_module.h"

#include <Arduino.h>
#include <Wire.h>

#include <MAX30105.h>

MAX30105 sensor;

//--------------------------------------------------
// Internal Variables
//--------------------------------------------------

static long irValue = 0;
static long redValue = 0;
static bool finger = false;

//--------------------------------------------------
// Initialization
//--------------------------------------------------

bool heartRateBegin()
{
    if (!sensor.begin(Wire))
        return false;

    // Recommended default configuration
    sensor.setup();

    sensor.setPulseAmplitudeRed(0x1F);
    sensor.setPulseAmplitudeIR(0x1F);

    return true;
}

//--------------------------------------------------
// Update Sensor
//--------------------------------------------------

void heartRateUpdate()
{
    sensor.check();

    while (sensor.available())
    {
        irValue = sensor.getIR();
        redValue = sensor.getRed();

        finger = (irValue > 5000);

        sensor.nextSample();
    }
}

//--------------------------------------------------
// Getters
//--------------------------------------------------

bool fingerDetected()
{
    return finger;
}

long getIRValue()
{
    return irValue;
}

long getRedValue()
{
    return redValue;
}