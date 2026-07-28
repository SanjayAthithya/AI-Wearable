#ifndef MAX30102_H
#define MAX30102_H

#include <Arduino.h>

//======================================
// I2C Address
//======================================

#define MAX30102_ADDRESS 0x57

//======================================
// Registers
//======================================

#define REG_INTR_STATUS_1      0x00
#define REG_INTR_STATUS_2      0x01
#define REG_INTR_ENABLE_1      0x02
#define REG_INTR_ENABLE_2      0x03

#define REG_FIFO_WR_PTR        0x04
#define REG_OVF_COUNTER        0x05
#define REG_FIFO_RD_PTR        0x06
#define REG_FIFO_DATA          0x07

#define REG_FIFO_CONFIG        0x08
#define REG_MODE_CONFIG        0x09
#define REG_SPO2_CONFIG        0x0A

#define REG_LED1_PA            0x0C
#define REG_LED2_PA            0x0D

#define REG_PART_ID            0xFF

//======================================
// Driver Functions
//======================================

bool max30102Begin();

void max30102Update();

bool max30102FingerDetected();

uint32_t getIR();

uint32_t getRed();

#endif