#include "wifi_stream.h"

#include <WiFi.h>

//==================================================
// User Configuration
//==================================================

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";

// Laptop IP Address
const char *SERVER_IP = "";

// TCP Port
const uint16_t SERVER_PORT = 5000;

//==================================================
// WiFi Client
//==================================================

WiFiClient client;

//==================================================
// Connect WiFi
//==================================================

bool wifiBegin()
{
    Serial.println();
    Serial.println("=================================");
    Serial.println("Connecting to WiFi...");
    Serial.println("=================================");

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");

        delay(500);

        if (millis() - start > 20000)
        {
            Serial.println();
            Serial.println("WiFi Connection Timeout");

            return false;
        }
    }

    Serial.println();
    Serial.println("WiFi Connected");

    Serial.print("ESP32 IP : ");
    Serial.println(WiFi.localIP());

//--------------------------------------
// Connect to Python
//--------------------------------------

    if (!wifiConnectServer())
    {
        return false;
    }

    return true;
}

//==================================================
// Connect to Python Server
//==================================================

bool wifiConnectServer()
{
    Serial.print("Connecting to Server... ");

    if (client.connect(SERVER_IP, SERVER_PORT))
    {
        Serial.println("OK");
        return true;
    }

    Serial.println("FAILED");

    return false;
}

//==================================================
// Send Packet
//==================================================

void wifiSend(const String &data)
{
    if (!client.connected())
    {
        wifiConnectServer();

        if (!client.connected())
            return;
    }

    client.println(data);
}

//==================================================
// Status
//==================================================

bool wifiConnected()
{
    return client.connected();
}