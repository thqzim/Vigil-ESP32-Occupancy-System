#include <Arduino.h>
#include "ESPNowReceiver.h"

extern OccupancyData occupancyData;
extern SemaphoreHandle_t occupancyMutex;

void onReceive(
    const esp_now_recv_info_t *info,
    const uint8_t *data,
    int len

    
)
{
    if(len != sizeof(OccupancyData))
        return;

    OccupancyData incoming;

    memcpy(
        &incoming,
        data,
        sizeof(incoming)
    );

    incoming.lastUpdate = millis();
    
    
    if(xSemaphoreTake(
    occupancyMutex,
    portMAX_DELAY
))
{
    occupancyData = incoming;

    xSemaphoreGive(
        occupancyMutex
    );
}

    Serial.print("Received: ");
    Serial.print((int)incoming.state);
    Serial.print("  ");
    Serial.println(incoming.confidence);


}

bool ESPNowReceiver::begin()
{
    WiFi.mode(WIFI_STA);

    if(esp_now_init() != ESP_OK)
        return false;

    esp_now_register_recv_cb(onReceive);

    return true;
}