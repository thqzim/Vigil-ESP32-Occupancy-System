#include <Arduino.h>
#include "Tasks.h"
#include "OLEDDisplay.h"
#include "OccupancyManager.h"

extern OLEDDisplay oled;


void OLEDTask(void *parameter)
{

    while(true)
    {

        OccupancyData data = getCurrentOccupancy();


        oled.update(data);


        vTaskDelay(
            pdMS_TO_TICKS(200)
        );

    }

}