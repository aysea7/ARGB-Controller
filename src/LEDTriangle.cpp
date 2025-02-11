#include <Arduino.h>
#include "IOManager.h"


void SendPWMToTriangle()
{
    analogWrite(pins.leds.triangleRed, IO.outputLevels.triangleRed);
    analogWrite(pins.leds.triangleGreen, IO.outputLevels.triangleGreen);
    analogWrite(pins.leds.triangleBlue, IO.outputLevels.triangleBlue);
};
