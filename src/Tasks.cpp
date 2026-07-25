#include <Arduino.h>
#include "Tasks.h"
#include "PIRSensor.h"
#include "UltrasonicSensor.h"
#include "Logic.h"
#include "OLEDDisplay.h"
#include "SharedData.h"

extern OccupancyData occupancyData;

extern SemaphoreHandle_t occupancyMutex;


extern PIRSensor pir;                         // don't make another variable
extern UltrasonicSensor ultrasonic; 
extern Logic logic;
extern OLEDDisplay oled;

void PIRTask(void *parameter)
{

    while(true)
    {

        pir.update();


        Serial.println(
            pir.isMotionDetected()
        );


        vTaskDelay(
            pdMS_TO_TICKS(100)
        );

    }

}

void UltrasonicTask(void *parameter)
{

    while(true)
    {

        ultrasonic.update();


        if(ultrasonic.hasValidReading())
        {
            Serial.print(
                ultrasonic.getDistance()
            );

            Serial.println(" cm");
        }

        else
        {
            Serial.println("Invalid");
        }



        vTaskDelay(
            pdMS_TO_TICKS(1000)
        );

    }

}

void LogicTask(void *parameter)
{

    while(true)
    {

        logic.update();

        Serial.println(
            logic.getStateName()
        );


        if(xSemaphoreTake(
            occupancyMutex,
            portMAX_DELAY
        ))
        {

            occupancyData.state =
                logic.getState();

            occupancyData.confidence =
                logic.getConfidence();

            xSemaphoreGive(
                occupancyMutex
            );

        }


        vTaskDelay(
            pdMS_TO_TICKS(1000)
        );

    }

}

void OLEDTask(void *parameter)
{

    while(true)
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


        oled.update(data);


        vTaskDelay(
            pdMS_TO_TICKS(500)
        );

    }

}