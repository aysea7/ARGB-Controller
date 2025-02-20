#include "Globals.h"
#include <Arduino.h>
#include "Config.h"

void IOManager::PollInputs()
{
    this->inputLevels.pots.red = AnalogReadTo8Bit(pins.pots.red);
    this->inputLevels.pots.green = AnalogReadTo8Bit(pins.pots.green);
    this->inputLevels.pots.blue = AnalogReadTo8Bit(pins.pots.blue);
    this->inputLevels.pots.brightness = AnalogReadTo8Bit(pins.pots.brightness);
    this->inputLevels.pots.temperature = AnalogReadTo8Bit(pins.pots.temperature);
    this->inputLevels.pots.triangleBrightnessScaling = AnalogReadTo8Bit(pins.pots.triangleBrightnessScaling);
    this->inputLevels.pots.settingsMode = analogRead(pins.pots.stripTypeAndLEDNumber);
    this->inputLevels.buttons.animations = !digitalRead(pins.buttons.animations);
    this->inputLevels.buttons.stripTypeAndIncr = !digitalRead(pins.buttons.stripTypeAndIncr);
    this->inputLevels.buttons.ledNumberAndDecr = !digitalRead(pins.buttons.ledNumberAndDecr);
    this->inputLevels.switches.indicatorLED = !digitalRead(pins.switches.indicatorLED);
    this->inputLevels.switches.mode1 = !digitalRead(pins.switches.mode1);
    this->inputLevels.switches.mode2 = !digitalRead(pins.switches.mode2);
    this->inputLevels.encoder.CW = !digitalRead(pins.encoder.CW);
    this->inputLevels.encoder.CCW = !digitalRead(pins.encoder.CCW);
};


void IOManager::UpdateOutputLevels() {
    this->UpdateTriangleLevels();
    ///this->outputLevels.data = GenerateDataForStrip();
};


void IOManager::UpdateTriangleLevels() {
    float globalBrightnessScaling = max(0.07f, this->inputLevels.pots.triangleBrightnessScaling / 1023.00f);
    
    float red;
    float green;
    float blue;

    if (stateMachine.systemState == COLOUR_SOLID)
    {
        red = (float)this->inputLevels.pots.red;
        green = (float)this->inputLevels.pots.green;
        blue = (float)this->inputLevels.pots.blue;
    }
    else if (stateMachine.systemState == COLOUR_ANIMATED)
    {
        red = (float)configs.leds[0].r;
        green = (float)configs.leds[0].g;
        blue = (float)configs.leds[0].b;
    }
    
    this->outputLevels.triangleRed = stateMachine.triangleState ? (uint8_t)(red * redIndLEDScalingFactor * globalBrightnessScaling) : 0;
    this->outputLevels.triangleGreen = stateMachine.triangleState ? (uint8_t)(green * greenIndLEDScalingFactor * globalBrightnessScaling) : 0;
    this->outputLevels.triangleBlue = stateMachine.triangleState ? (uint8_t)(blue * blueIndLEDScalingFactor * globalBrightnessScaling) : 0;
};


uint8_t IOManager::AnalogReadTo8Bit(uint8_t pin)
{
    return analogRead(pin) >> 2;
};
