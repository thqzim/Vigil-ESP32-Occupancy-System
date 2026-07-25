#include <Arduino.h>
#include "Logic.h"



Logic::Logic(
    PIRSensor& p,
    UltrasonicSensor& u
)
:
pir(p),
ultrasonic(u)

{

    confidence = 0;

    currentState = State::EMPTY;

}



void Logic::update()
{

    // decay

    confidence -= 5;


    if(confidence < 0)
        confidence = 0;



    // PIR evidence

    if(pir.consumeMotionEvent())
{
    confidence += 30;
}



    // Ultrasonic evidence

    if(
      ultrasonic.hasValidReading()
      &&
      ultrasonic.getDistance() < 150
    )
    {

        confidence += 20;

    }



    if(confidence > 100)
        confidence = 100;



    if(confidence >= 70)
    {
        currentState = State::OCCUPIED;
    }

    else if(confidence <= 30)
    {
        currentState = State::EMPTY;
    }

    else
    {
        currentState = State::TRANSITION;
    }

}



float Logic::getConfidence()
{
    return confidence;
}



State Logic::getState()
{
    return currentState;
}



String Logic::getStateName()
{

    switch(currentState)
    {

        case State::EMPTY:
            return "EMPTY";


        case State::OCCUPIED:
            return "OCCUPIED";


        case State::TRANSITION:
            return "TRANSITION";

    }


    return "UNKNOWN";

}