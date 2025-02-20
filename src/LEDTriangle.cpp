#include "Globals.h"
#include "LEDTriangle.h"
#include <Arduino.h>


void SendPWMToTriangle()
{
    analogWrite(pins.leds.triangleRed, IO.outputLevels.triangleRed);
    analogWrite(pins.leds.triangleGreen, IO.outputLevels.triangleGreen);
    analogWrite(pins.leds.triangleBlue, IO.outputLevels.triangleBlue);
};
