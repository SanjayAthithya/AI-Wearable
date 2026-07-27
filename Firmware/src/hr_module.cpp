#include "hr_module.h"

#include <Arduino.h>
#include <Wire.h>

#include "MAX30102.h"
#include "Pulse.h"

MAX30102 sensor;
Pulse pulseIR;
Pulse pulseRed;
MAFilter bpmFilter;

//--------------------------------------------------
// Internal variables
//--------------------------------------------------

static long irValue = 0;
static long redValue = 0;

static bool finger = false;

static int bpm = 0;
static int spo2 = 0;

static bool bpm_ok = false;
static bool spo2_ok = false;

static unsigned long lastBeat = 0;

static bool filterGraph = false;
static bool drawRed = false;

//--------------------------------------------------
// Initialization
//--------------------------------------------------

bool heartRateBegin()
{

    if (!sensor.begin())
        return false;

    sensor.setup();

    return true;
}

//--------------------------------------------------
// Update
//--------------------------------------------------

//--------------------------------------------------
// Update
//--------------------------------------------------

void heartRateUpdate()
{
    sensor.check();

    while (sensor.available())
    {
        // Read latest sample
        irValue = sensor.getIR();
        redValue = sensor.getRed();

        sensor.nextSample();

        // Finger detection
        finger = (irValue > 5000);

        if (!finger)
        {
            bpm = 0;
            bpm_ok = false;
            lastBeat = 0;
            return;
        }

        //----------------------------------
        // Remove DC component
        //----------------------------------

        int16_t irSignal;
        int16_t redSignal;

        bool beatIR;
        bool beatRed;

        if (!filterGraph)
        {
            irSignal = pulseIR.dc_filter(irValue);
            redSignal = pulseRed.dc_filter(redValue);

            beatIR = pulseIR.isBeat(
                pulseIR.ma_filter(irSignal));

            beatRed = pulseRed.isBeat(
                pulseRed.ma_filter(redSignal));
        }
        else
        {
            irSignal =
                pulseIR.ma_filter(
                    pulseIR.dc_filter(irValue));

            redSignal =
                pulseRed.ma_filter(
                    pulseRed.dc_filter(redValue));

            beatIR = pulseIR.isBeat(irSignal);
            beatRed = pulseRed.isBeat(redSignal);
        }

        //----------------------------------
        // Beat detected?
        //----------------------------------

        if (drawRed ? beatRed : beatIR)
        {
            unsigned long now = millis();

            if (lastBeat != 0)
            {
                unsigned long delta = now - lastBeat;

                if (delta > 0)
                {
                    int btpm = 60000 / delta;

                    if (btpm >= 35 && btpm <= 220)
                    {
                        bpm = bpmFilter.filter(btpm);
                        bpm_ok = true;

                        // Temporary placeholder SpO₂
                        long numerator =
                            (pulseRed.avgAC() * pulseIR.avgDC()) / 256;

                        long denominator =
                            (pulseRed.avgDC() * pulseIR.avgAC()) / 256;

                        if (denominator > 0)
                        {
                            int rx100 = (numerator * 100) / denominator;

                            spo2 = (10400 - (17 * rx100) + 50) / 100;

                            if (spo2 > 100)
                                spo2 = 100;

                            if (spo2 < 80)
                                spo2 = 80;

                            spo2_ok = true;
                        }
                    }
                }
            }

            lastBeat = now;
        }
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

int getBPM()
{
    return bpm;
}

int getSpO2()
{
    return spo2;
}

bool bpmValid()
{
    return bpm_ok;
}

bool spo2Valid()
{
    return spo2_ok;
}