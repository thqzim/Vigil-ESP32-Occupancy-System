#ifndef ESPNOWRECEIVER_H
#define ESPNOWRECEIVER_H

#include <WiFi.h>
#include <esp_now.h>

#include "SharedData.h"

class ESPNowReceiver
{
public:

    bool begin();

};

#endif