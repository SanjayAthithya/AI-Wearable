#include "max30102.h"

#include <Wire.h>

static uint32_t irValue = 0;
static uint32_t redValue = 0;

//--------------------------------------
// Write Register
//--------------------------------------

void writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(MAX30102_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

//--------------------------------------
// Read Register
//--------------------------------------

uint8_t readRegister(uint8_t reg)
{
    Wire.beginTransmission(MAX30102_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(MAX30102_ADDRESS, 1);

    if (Wire.available())
        return Wire.read();

    return 0;
}

//--------------------------------------
// Initialize Sensor
//--------------------------------------

bool max30102Begin()
{
    Wire.begin(21,22);

    uint8_t partID = readRegister(REG_PART_ID);

    if(partID != 0x15)
        return false;

    // Reset
    writeRegister(REG_MODE_CONFIG,0x40);

    delay(100);

    // FIFO
    writeRegister(REG_FIFO_WR_PTR,0x00);
    writeRegister(REG_OVF_COUNTER,0x00);
    writeRegister(REG_FIFO_RD_PTR,0x00);

    // FIFO Config
    writeRegister(REG_FIFO_CONFIG,0x0F);

    // SPO2 Config
    writeRegister(REG_SPO2_CONFIG,0x27);

    // LED Brightness
    writeRegister(REG_LED1_PA,0x24);
    writeRegister(REG_LED2_PA,0x24);

    // SPO2 Mode
    writeRegister(REG_MODE_CONFIG,0x03);

    return true;
}

//--------------------------------------
// Read FIFO
//--------------------------------------

void max30102Update()
{
    Wire.beginTransmission(MAX30102_ADDRESS);
    Wire.write(REG_FIFO_DATA);
    Wire.endTransmission(false);

    Wire.requestFrom(MAX30102_ADDRESS,6);

    if(Wire.available()==6)
    {
        irValue =
        ((uint32_t)Wire.read()<<16)|
        ((uint32_t)Wire.read()<<8)|
        Wire.read();

        irValue &= 0x03FFFF;

        redValue =
        ((uint32_t)Wire.read()<<16)|
        ((uint32_t)Wire.read()<<8)|
        Wire.read();

        redValue &= 0x03FFFF;
    }
}

//--------------------------------------
// Finger Detection
//--------------------------------------

bool max30102FingerDetected()
{
    return (irValue > 10000);
}

//--------------------------------------
// Getters
//--------------------------------------

uint32_t getIR()
{
    return irValue;
}

uint32_t getRed()
{
    return redValue;
}