#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include "SystemState.h"

struct OccupancyData
{
    State state;
    float confidence;
    unsigned long lastUpdate;
};

#endif