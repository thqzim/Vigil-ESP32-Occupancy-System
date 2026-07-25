#include "PIRSensor.h"
#include "UltrasonicSensor.h"
#include "Logic.h"
#include "OLEDDisplay.h"
#include "Tasks.h"
#include "SharedData.h"


PIRSensor pir(4);

UltrasonicSensor ultrasonic(5,18);

Logic logic(pir, ultrasonic);

OLEDDisplay oled;

OccupancyData occupancyData =
{
    State::EMPTY,
    0
};

SemaphoreHandle_t occupancyMutex;

void setup()
{
    Serial.begin(115200);

    oled.begin();

    occupancyMutex = xSemaphoreCreateMutex();


    xTaskCreate(
        PIRTask,
        "PIR Task",
        2048,
        NULL,
        2,                             //higher priority
        NULL
    );

    xTaskCreate(
        UltrasonicTask,
        "Ultrasonic Task",
        2048,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        LogicTask,
        "Logic Task",
        2048,
        NULL,
        2,
        NULL
    );

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

}