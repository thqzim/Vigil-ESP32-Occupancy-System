#include <Arduino.h>
#include "PIRSensor.h"



PIRSensor::PIRSensor(int pirPin)
{

    pin = pirPin;

    pinMode(pin, INPUT);

    pirDetected = false;

    lastMotionTime = 0;

}



void PIRSensor::update()
{

    bool currentReading = digitalRead(pin);


    if(currentReading && !pirDetected)
        {
             motionEvent = true;

            lastMotionTime = millis();
        }       


    pirDetected = currentReading;
}

bool PIRSensor::isMotionDetected()
{
    return pirDetected;
}



unsigned long PIRSensor::getLastMotionTime()
{
    return lastMotionTime;
}

bool PIRSensor::consumeMotionEvent()
{
    if(motionEvent)
    {
        motionEvent = false;
        return true;
    }

    return false;
}