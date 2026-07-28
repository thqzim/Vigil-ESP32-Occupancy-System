#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "OLEDDisplay.h"
#include "Tasks.h"
#include "SharedData.h"
#include "ESPNowReceiver.h"
#include "dashboard.h"
#include "OccupancyManager.h"

ESPNowReceiver receiver;
OLEDDisplay oled;
WebServer server(80);
OccupancyData occupancyData =
{
    State::EMPTY,
    0,
    0
};

SemaphoreHandle_t occupancyMutex;

const char* ssid = "YOUR_WIFI_NAME";                           //insert wifi name
const char* password = "YOUR_WIFI_PASSWORD";                   //insert wifi password

void handleRoot()
{
    server.send(
        200,
        "text/html",
        dashboardHTML
    );
}

void handleStatus()
{
    OccupancyData data = getCurrentOccupancy();


    String stateText;


    switch(data.state)
    {
        case State::EMPTY:
            stateText = "EMPTY";
            break;

        case State::OCCUPIED:
            stateText = "OCCUPIED";
            break;

        case State::TRANSITION:
            stateText = "TRANSITION";
            break;

        case State::NO_SIGNAL:
            stateText = "NO_SIGNAL";
            break;
    }


    bool connected =
        data.state != State::NO_SIGNAL;


    String json = "{";

    json += "\"state\":\"";
    json += stateText;
    json += "\",";


    json += "\"confidence\":";
    json += String(data.confidence);
    json += ",";


    json += "\"connected\":";
    json += connected ? "true" : "false";


    json += "}";


    server.send(
        200,
        "application/json",
        json
    );
}

void setup()
{
    Serial.begin(115200);

    occupancyMutex = xSemaphoreCreateMutex();

    oled.begin();

    if(!receiver.begin())
    {
        Serial.println("ESP-NOW failed");
        while(true);
    }


    WiFi.begin(
        ssid,
        password
    );

    Serial.print("Connecting to WiFi");

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();

    Serial.println("WiFi connected");

    Serial.println(
        WiFi.localIP()
    );

    Serial.println(WiFi.channel());


    server.on(
        "/",
        handleRoot
    );

    server.on(
    "/status",
    handleStatus
);

    server.begin();

    Serial.println("HTTP server started");


    xTaskCreate(
        OLEDTask,
        "OLED Task",
        4096,
        NULL,
        1,
        NULL
    );
}

void loop()
{
    server.handleClient();
}