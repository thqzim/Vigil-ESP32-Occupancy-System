#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <Arduino.h>
#include "SystemState.h"

struct OccupancyData
{
    State state;
    float confidence;
    unsigned long lastUpdate;
};

#endif