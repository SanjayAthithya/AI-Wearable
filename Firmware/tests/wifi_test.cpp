#include "wifi_stream.h"

#include <WiFi.h>

//==================================================
// WiFi Configuration
//==================================================

const char *WIFI_SSID = "ALFRED 0008";
const char *WIFI_PASSWORD = "YOUR_PASSWORD";

// Laptop Hotspot IP
const char *SERVER_IP = "192.168.137.1";

const uint16_t SERVER_PORT = 5000;

//==================================================

WiFiClient client;

//==================================================
// Begin
//==================================================

bool wifiBegin()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("=================================");
    Serial.println("Initializing WiFi...");
    Serial.println("=================================");

    WiFi.mode(WIFI_STA);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();

    Serial.println("WiFi Connected");

    Serial.print("IP : ");
    Serial.println(WiFi.localIP());

    Serial.print("Connecting to Python... ");

    if (!client.connect(SERVER_IP, SERVER_PORT))
    {
        Serial.println("FAILED");
        return false;
    }

    Serial.println("SUCCESS");

    return true;
}

//==================================================
// Send
//==================================================

void wifiSend(const String &data)
{
    if (!client.connected())
        return;

    client.println(data);
}

//==================================================
// Status
//==================================================

bool wifiConnected()
{
    return client.connected();
}