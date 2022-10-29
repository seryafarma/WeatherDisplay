//------------------------------------------------------------------------------
// Wifi_Blink.ino
// File to show simply on how to connect to a wifi using SSID and Password.
// Style: Procedural
//------------------------------------------------------------------------------

// Example output:
// Connecting to Wifi SSID
// .......
// WiFi connected!
// 192.168.1.63

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include <ESP8266WiFi.h>

#include "Private_SSID_Pass.h" // Add your SSID and PASS here.

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Functions Declaration
//------------------------------------------------------------------------------
void connectWifi();

//------------------------------------------------------------------------------
// Setup and Loop
//------------------------------------------------------------------------------
void setup()
{
    Serial.begin(9600);
    delay(1500);
    connectWifi();
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
}

//------------------------------------------------------------------------------
// Functions Definition
//------------------------------------------------------------------------------
void connectWifi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.println(WiFi.localIP());
    Serial.println();
}
