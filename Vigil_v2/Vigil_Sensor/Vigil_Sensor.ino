#include "PIRSensor.h"
#include "UltrasonicSensor.h"
#include "Logic.h"
#include "Tasks.h"
#include "SharedData.h"
#include "ESPNowSender.h"

ESPNowSender sender;

PIRSensor pir(4);

UltrasonicSensor ultrasonic(5,18);

Logic logic(pir, ultrasonic);


OccupancyData occupancyData =
{
    State::EMPTY,
    0
};

SemaphoreHandle_t occupancyMutex;

void setup()
{
    Serial.begin(115200);

    occupancyMutex = xSemaphoreCreateMutex();

    if(!sender.begin())
{
    Serial.println("ESP-NOW initialization failed");

    while(true);
}


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

   
}



void loop()
{

}