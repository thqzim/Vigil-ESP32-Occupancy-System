#ifndef PIRSENSOR_H
#define PIRSENSOR_H


class PIRSensor
{

private:

    int pin;

    bool pirDetected;

    bool motionEvent;

    unsigned long lastMotionTime;


public:

    PIRSensor(int pirPin);

    void update();

    bool isMotionDetected();

    unsigned long getLastMotionTime();

    bool consumeMotionEvent();

};


#endif