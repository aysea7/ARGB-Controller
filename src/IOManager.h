#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <Arduino.h>
#include "Config.h"


class IOManager
{
public:
    struct InputLevels {
        struct Pots {
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            uint8_t brightness;
            uint8_t temperature;
            uint8_t triangleBrightnessScaling;
            bool stripTypeMode;
            bool LEDNumberMode;
        } pots;

        struct Buttons {
            bool stripTypeAndIncr;
            bool ledNumberAndDecr;
            bool animations;
        } buttons;

        struct Switches {
            bool indicatorLED;
            bool mode1;
            bool mode2;
        } switches;

        struct Encoder {
            bool CW;
            bool CCW;
        } encoder;
    } inputLevels;

    struct OutputLevels
    {
        uint8_t triangleRed;
        uint8_t triangleGreen;
        uint8_t triangleBlue;
        uint8_t data;
    } outputLevels;

    void PollInputs();

    void UpdateOutputLevels();

    void UpdateTriangleLevels();
    
    uint8_t AnalogReadTo8Bit(uint8_t pin);

};

extern IOManager IO;


#endif