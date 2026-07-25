#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H


class UltrasonicSensor
{

private:

    int trigPin;
    int echoPin;


    float filteredDistance;

    float candidateDistance;


    int stableCount;


    bool validReading;



public:

    UltrasonicSensor(int trig, int echo);


    void update();


    float getDistance();


    bool hasValidReading();


};



#endif