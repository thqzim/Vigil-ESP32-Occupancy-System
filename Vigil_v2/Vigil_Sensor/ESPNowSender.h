#ifndef ESPNOWSENDER_H
#define ESPNOWSENDER_H

#include <esp_now.h>
#include <WiFi.h>

#include "SharedData.h"

class ESPNowSender
{
private:

    uint8_t receiverMAC[6];

public:

    ESPNowSender();

    bool begin();

    void send(OccupancyData data);
};

#endif