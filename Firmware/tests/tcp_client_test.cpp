#include <Arduino.h>
#include <WiFi.h>

//==================================================
// WiFi Credentials
//==================================================

const char* WIFI_SSID = "ALFRED 0008";
const char* WIFI_PASSWORD = "Batman1234";

//==================================================
// Python Server
//==================================================

// Replace with YOUR laptop hotspot IPv4 address
const char* SERVER_IP = "192.168.137.4";

const uint16_t SERVER_PORT = 5000;

//==================================================

WiFiClient client;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("==================================");
    Serial.println("       TCP CLIENT TEST");
    Serial.println("==================================");

    //--------------------------------------
    // Connect WiFi
    //--------------------------------------

    WiFi.mode(WIFI_STA);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi Connected");

    Serial.print("ESP32 IP : ");
    Serial.println(WiFi.localIP());

    //--------------------------------------
    // Connect Python Server
    //--------------------------------------

    Serial.print("Connecting to Python Server... ");

    if (client.connect(SERVER_IP, SERVER_PORT))
    {
        Serial.println("SUCCESS");

        client.println("HELLO FROM ESP32");
    }
    else
    {
        Serial.println("FAILED");
    }
}

void loop()
{
    static unsigned long lastSend = 0;

    if (client.connected())
    {
        if (millis() - lastSend >= 5000)
        {
            lastSend = millis();

            client.println("Heartbeat from ESP32");
        }
    }
}