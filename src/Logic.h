#ifndef LOGIC_H
#define LOGIC_H


#include "SystemState.h"
#include "PIRSensor.h"
#include "UltrasonicSensor.h"



class Logic
{

private:

    PIRSensor& pir;

    UltrasonicSensor& ultrasonic;



    float confidence;


    State currentState;



public:

    Logic(
        PIRSensor& p,
        UltrasonicSensor& u
    );


    void update();


    float getConfidence();


    State getState();


    String getStateName();

};



#endif