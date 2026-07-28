#include <Arduino.h>
#include "UltrasonicSensor.h"



UltrasonicSensor::UltrasonicSensor(
    int trig,
    int echo
)
{

    trigPin = trig;
    echoPin = echo;


    pinMode(trigPin, OUTPUT);

    pinMode(echoPin, INPUT);



    filteredDistance = 0;

    candidateDistance = 0;


    stableCount = 0;


    validReading = false;

}



void UltrasonicSensor::update()
{

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);


    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);


    digitalWrite(trigPin, LOW);



    long duration = pulseIn(
        echoPin,
        HIGH,
        30000
    );



    float newDistance =
        duration * 0.0343 / 2;



    if(newDistance <= 0 ||
       newDistance > 200)
    {

        validReading = false;
        return;

    }



    if(filteredDistance == 0)
    {

        filteredDistance = newDistance;

        candidateDistance = newDistance;

        validReading = true;

        return;

    }



    if(abs(newDistance - candidateDistance) <= 5)
    {

        stableCount++;

    }

    else
    {

        candidateDistance = newDistance;

        stableCount = 1;

    }



    if(stableCount >= 3)
    {

        filteredDistance = candidateDistance;

        stableCount = 0;

    }



    validReading = true;

}



float UltrasonicSensor::getDistance()
{
    return filteredDistance;
}



bool UltrasonicSensor::hasValidReading()
{
    return validReading;
}