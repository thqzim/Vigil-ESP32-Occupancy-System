#ifndef OLEDDISPLAY_H
#define OLEDDISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SharedData.h"



class OLEDDisplay
{

private:

    Adafruit_SSD1306 display;



public:

    OLEDDisplay();

    void begin(); 

    void update(OccupancyData data);

};


#endif