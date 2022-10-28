//------------------------------------------------------------------------------
// Snapshot.ino
// File to show a snapshot of a JSON response to show on the display. The
// snapshot contains the weather information we want to show.
// Style: Procedural
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <SPI.h>

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN 5
#define DATA_PIN 7
#define CS_PIN 4

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const char *ESP_HOST_NAME = "Blue_ESP";
const char *WIFI_SSID = "Wifi van de buren";
const char *WIFI_PASSWORD = "Landheer22#!";
const char *weather = NULL;
const char *weather_desc = NULL;
const char *name = NULL;
double temp = 0.0;
long hum = 0;

String things_to_show;

char json[] =
    "{\"coord\":{\"lon\":5.46,\"lat\":51.44},\"weather\":[{\"id\":804,\"main\":"
    "\"Clouds\",\"description\":\"overcast "
    "clouds\",\"icon\":\"04d\"}],\"base\":\"stations\",\"main\":{\"temp\":295."
    "14,\"feels_like\":295.09,\"temp_min\":293.03,\"temp_max\":296.54,"
    "\"pressure\":1016,\"humidity\":65},\"visibility\":10000,\"wind\":{"
    "\"speed\":4.12,\"deg\":230},\"clouds\":{\"all\":100},\"dt\":1666964435,"
    "\"sys\":{\"type\":1,\"id\":1527,\"country\":\"NL\",\"sunrise\":1666938240,"
    "\"sunset\":1666973982},\"timezone\":7200,\"id\":2756252,\"name\":"
    "\"Gemeente Eindhoven\",\"cod\":200}";

//------------------------------------------------------------------------------
// Functions Declaration
//------------------------------------------------------------------------------
void parse_json(char *json);

//------------------------------------------------------------------------------
// Setup and Loop
//------------------------------------------------------------------------------
void setup()
{
    Serial.begin(115200);
    parse_json(json);
    P.begin();
}

void loop()
{
    things_to_show.clear();
    // Add the name.
    things_to_show = name;
    // Separator.
    things_to_show.concat(". ");
    // Add the weather.
    things_to_show.concat(weather);
    things_to_show.concat(": ");
    things_to_show.concat(weather_desc);
    // Separator.
    things_to_show.concat(". ");
    // Add the temperature.
    things_to_show.concat("Temperature: ");
    things_to_show.concat(String(temp) + " C");
    // Separator.
    things_to_show.concat(". ");
    // Add the humidity.
    things_to_show.concat("Humidity: ");
    things_to_show.concat(String(hum) + " %");
    // Separator.
    things_to_show.concat(". ");

    if (P.displayAnimate())
    {
        P.displayText(things_to_show.c_str(), PA_LEFT, 100, 100, PA_SCROLL_LEFT,
                      PA_SCROLL_LEFT);
    }
}

//------------------------------------------------------------------------------
// Functions Definition
//------------------------------------------------------------------------------
void parse_json(char *json)
{
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);

    weather = doc["weather"][0]["main"];
    weather_desc = doc["weather"][0]["description"];
    temp = doc["main"]["temp"];
    temp -= 273.15;
    long press = doc["main"]["pressure"];
    hum = doc["main"]["humidity"];
    name = doc["name"];
}
