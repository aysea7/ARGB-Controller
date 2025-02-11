#include <Arduino.h>
#include "IOManager.h"
#include "Config.h"


IOManager IO;

void IOManager::PollInputs()
{
    this->inputLevels.pots.red = AnalogReadTo8Bit(pins.pots.red);
    this->inputLevels.pots.green = AnalogReadTo8Bit(pins.pots.green);
    this->inputLevels.pots.blue = AnalogReadTo8Bit(pins.pots.blue);
    this->inputLevels.pots.brightness = AnalogReadTo8Bit(pins.pots.brightness);
    this->inputLevels.pots.temperature = AnalogReadTo8Bit(pins.pots.temperature);
    this->inputLevels.pots.triangleBrightnessScaling = AnalogReadTo8Bit(pins.pots.triangleBrightnessScaling);

    if (analogRead(pins.pots.stripTypeAndLEDNumber) > 511)
    {
        this->inputLevels.pots.LEDNumberMode = true;
        this->inputLevels.pots.stripTypeMode = false;
    } else {
        this->inputLevels.pots.LEDNumberMode = false;
        this->inputLevels.pots.stripTypeMode = true;
    }

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
    bool triangleOn = this->inputLevels.switches.indicatorLED;
    float globalBrightnessScaling = max(0.07f, this->inputLevels.pots.triangleBrightnessScaling / 1023.00f);
    
    this->outputLevels.triangleRed = triangleOn ? (uint8_t)((float)this->inputLevels.pots.red * redIndLEDScalingFactor * globalBrightnessScaling) : 0;
    this->outputLevels.triangleGreen = triangleOn ? (uint8_t)((float)this->inputLevels.pots.green * greenIndLEDScalingFactor * globalBrightnessScaling) : 0;
    this->outputLevels.triangleBlue = triangleOn ? (uint8_t)((float)this->inputLevels.pots.blue * blueIndLEDScalingFactor * globalBrightnessScaling) : 0;
};


uint8_t IOManager::AnalogReadTo8Bit(uint8_t pin)
{
    return analogRead(pin) >> 2;
};
