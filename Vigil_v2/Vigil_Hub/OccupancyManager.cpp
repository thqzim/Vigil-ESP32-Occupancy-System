#include <Arduino.h>
#include "OccupancyManager.h"

extern OccupancyData occupancyData;
extern SemaphoreHandle_t occupancyMutex;


OccupancyData getCurrentOccupancy()
{
    OccupancyData data;


    if(xSemaphoreTake(
        occupancyMutex,
        portMAX_DELAY
    ))
    {
        data = occupancyData;

        xSemaphoreGive(
            occupancyMutex
        );
    }


    if(
        millis() - data.lastUpdate > 5000
    )
    {
        data.state = State::NO_SIGNAL;
        data.confidence = 0;
    }


    return data;
}