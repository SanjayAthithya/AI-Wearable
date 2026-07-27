#include "oled.h"

#include <Wire.h>

//==================================================
// OLED Object
//==================================================

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(
    U8G2_R0,
    U8X8_PIN_NONE
);

//==================================================
// Page Variables
//==================================================

static uint8_t currentPage = 0;

static unsigned long lastPageChange = 0;

const unsigned long PAGE_TIME = 2000;   // 2 seconds

//==================================================
// Initialize OLED
//==================================================

bool oledBegin()
{
    oled.begin();

    oled.clearBuffer();
    oled.sendBuffer();

    oledSplash();

    lastPageChange = millis();

    return true;
}

//==================================================
// Splash Screen
//==================================================

void oledSplash()
{
    oled.clearBuffer();

    oled.setFont(u8g2_font_ncenB14_tr);
    oled.drawStr(10,22,"AI Wearable");

    oled.setFont(u8g2_font_6x12_tr);
    oled.drawStr(22,45,"Initializing...");

    oled.sendBuffer();

    delay(2000);
}

//==================================================
// Change Page
//==================================================

void oledNextPage()
{
    currentPage++;

    if(currentPage > 3)
        currentPage = 0;
}

//==================================================
// Update Display
//==================================================

void oledUpdate()
{
    if(millis() - lastPageChange >= PAGE_TIME)
    {
        lastPageChange = millis();

        oledNextPage();
    }

    switch(currentPage)
    {
        case 0:
            oledHeartPage();
            break;

        case 1:
            oledAccelPage();
            break;

        case 2:
            oledGyroPage();
            break;

        case 3:
            oledTempPage();
            break;
    }
}
//==================================================
// Heart Sensor Page
//==================================================

void oledHeartPage()
{
    oled.clearBuffer();

    //----------------------------------------
    // Title
    //----------------------------------------

    oled.setFont(u8g2_font_ncenB08_tr);
    oled.drawStr(18,12,"AI Wearable");

    oled.setFont(u8g2_font_6x12_tr);

    //----------------------------------------
    // Finger Status
    //----------------------------------------

    oled.drawStr(0,28,"Finger :");

    if (fingerDetected())
        oled.drawStr(60,28,"YES");
    else
        oled.drawStr(60,28,"NO");

    //----------------------------------------
    // IR Value
    //----------------------------------------

    oled.drawStr(0,42,"IR :");
    oled.setCursor(35,42);
    oled.print(getIRValue());

    //----------------------------------------
    // RED Value
    //----------------------------------------

    oled.drawStr(0,54,"RED:");
    oled.setCursor(35,54);
    oled.print(getRedValue());

    //----------------------------------------
    // BPM
    //----------------------------------------

    oled.drawStr(0,66,"BPM:");

    oled.setCursor(35,66);

    if (bpmValid())
        oled.print(getBPM());
    else
        oled.print("--");

    //----------------------------------------
    // SpO2
    //----------------------------------------

    oled.drawStr(70,66,"SpO2:");

    oled.setCursor(108,66);

    if (spo2Valid())
    {
        oled.print(getSpO2());
        oled.print("%");
    }
    else
    {
        oled.print("--");
    }

    oled.sendBuffer();
}
//==================================================
// Accelerometer Page
//==================================================

void oledAccelPage()
{
    IMUData imu = getIMUData();

    oled.clearBuffer();

    oled.setFont(u8g2_font_ncenB08_tr);
    oled.drawStr(18,12,"ACCELEROMETER");

    oled.setFont(u8g2_font_6x12_tr);

    oled.drawStr(0,28,"X :");
    oled.setCursor(28,28);
    oled.print(imu.accX,3);

    oled.drawStr(0,42,"Y :");
    oled.setCursor(28,42);
    oled.print(imu.accY,3);

    oled.drawStr(0,56,"Z :");
    oled.setCursor(28,56);
    oled.print(imu.accZ,3);

    oled.sendBuffer();
}

//==================================================
// Gyroscope Page
//==================================================

void oledGyroPage()
{
    IMUData imu = getIMUData();

    oled.clearBuffer();

    oled.setFont(u8g2_font_ncenB08_tr);
    oled.drawStr(28,12,"GYROSCOPE");

    oled.setFont(u8g2_font_6x12_tr);

    oled.drawStr(0,28,"X :");
    oled.setCursor(28,28);
    oled.print(imu.gyroX,2);

    oled.drawStr(0,42,"Y :");
    oled.setCursor(28,42);
    oled.print(imu.gyroY,2);

    oled.drawStr(0,56,"Z :");
    oled.setCursor(28,56);
    oled.print(imu.gyroZ,2);

    oled.sendBuffer();
}

//==================================================
// Temperature Page
//==================================================

void oledTempPage()
{
    IMUData imu = getIMUData();

    oled.clearBuffer();

    oled.setFont(u8g2_font_ncenB08_tr);
    oled.drawStr(22,15,"TEMPERATURE");

    oled.setFont(u8g2_font_logisoso20_tr);

    oled.setCursor(15,50);
    oled.print(imu.temperature,1);

    oled.print(" C");

    oled.sendBuffer();
}