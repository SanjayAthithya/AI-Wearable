#include "oled.h"

#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0);

//======================================
// Initialization
//======================================

bool oledBegin()
{
    oled.begin();

    oled.clearBuffer();
    oled.setFont(u8g2_font_6x12_tf);
    oled.drawStr(25, 30, "OLED READY");
    oled.sendBuffer();

    delay(1000);

    return true;
}

//======================================
// Clear Screen
//======================================

void oledClear()
{
    oled.clearBuffer();
    oled.sendBuffer();
}

//======================================
// Boot Screen
//======================================

void oledShowBoot()
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_ncenB10_tr);
    oled.drawStr(8,22,"AI WEARABLE");

    oled.setFont(u8g2_font_6x12_tf);
    oled.drawStr(18,48,"Initializing...");

    oled.sendBuffer();
}

//======================================
// Health Screen
//======================================

void oledShowHealth(
    int heartRate,
    int spo2,
    float temperature,
    float battery)
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_6x12_tf);

    oled.setCursor(0,15);
    oled.print("HR : ");
    oled.print(heartRate);
    oled.print(" bpm");

    oled.setCursor(0,30);
    oled.print("SpO2 : ");
    oled.print(spo2);
    oled.print("%");

    oled.setCursor(0,45);
    oled.print("Temp : ");
    oled.print(temperature,1);
    oled.print(" C");

    oled.setCursor(0,60);
    oled.print("BAT : ");
    oled.print(battery,0);
    oled.print("%");

    oled.sendBuffer();
}

//======================================
// Motion Screen (LIVE MPU6500)
//======================================

void oledShowMotion(
    float accX,
    float accY,
    float accZ,
    float gyroX,
    float gyroY,
    float gyroZ)
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_6x12_tf);

    // Accelerometer
    oled.setCursor(0,12);
    oled.print("AX:");
    oled.print(accX,2);

    oled.setCursor(64,12);
    oled.print("GX:");
    oled.print(gyroX,1);

    oled.setCursor(0,28);
    oled.print("AY:");
    oled.print(accY,2);

    oled.setCursor(64,28);
    oled.print("GY:");
    oled.print(gyroY,1);

    oled.setCursor(0,44);
    oled.print("AZ:");
    oled.print(accZ,2);

    oled.setCursor(64,44);
    oled.print("GZ:");
    oled.print(gyroZ,1);

    oled.drawLine(0,52,127,52);

    oled.setCursor(18,63);
    oled.print("MPU6500 LIVE");

    oled.sendBuffer();
}

//======================================
// Alert Screen
//======================================

void oledShowAlert(const String &message)
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_ncenB08_tr);
    oled.drawStr(12,18,"!!! ALERT !!!");

    oled.setFont(u8g2_font_6x12_tf);

    oled.setCursor(0,42);
    oled.print(message);

    oled.sendBuffer();
}

//======================================
// Debug Screen
//======================================

void oledShowDebug(
    uint32_t ir,
    uint32_t red,
    bool wifiStatus)
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_6x12_tf);

    oled.setCursor(0,15);
    oled.print("IR : ");
    oled.print(ir);

    oled.setCursor(0,30);
    oled.print("RED: ");
    oled.print(red);

    oled.setCursor(0,45);
    oled.print("WiFi: ");

    if(wifiStatus)
        oled.print("ON");
    else
        oled.print("OFF");

    oled.sendBuffer();
}