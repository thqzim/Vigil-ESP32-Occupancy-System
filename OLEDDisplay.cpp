#include "OLEDDisplay.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


OLEDDisplay::OLEDDisplay()
:
display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
)
{

}



void OLEDDisplay::begin()
{
    Wire.begin();


    if(!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C
    ))
    {
        Serial.println("OLED initialization failed");

        while(true);
    }


    display.clearDisplay();


    display.setTextColor(
        SSD1306_WHITE
    );
}



void OLEDDisplay::update(
    OccupancyData data
)
{
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0,0);

    display.println(
        "Occupancy System"
    );


    display.setTextSize(2);
    display.setCursor(0,18);


    switch(data.state)
    {

        case State::EMPTY:
            display.println("EMPTY");
            break;


        case State::OCCUPIED:
            display.println("OCCUPIED");
            break;


        case State::TRANSITION:
            display.println("TRANSITION");
            break;

    }


    display.setTextSize(1);

    display.setCursor(0,50);

    display.print("Confidence: ");

    display.print(data.confidence);

    display.println("%");


    display.display();
}