#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <FastLED.h>


struct Pins {
    struct Pots {
        static constexpr uint8_t red = A3;
        static constexpr uint8_t green = A4;
        static constexpr uint8_t blue = A5;
        static constexpr uint8_t brightness = A6;
        static constexpr uint8_t temperature = A7;
        static constexpr uint8_t triangleBrightnessScaling = A0;
        static constexpr uint8_t stripTypeAndLEDNumber = A2;
    } pots;

    struct Buttons {
        static constexpr uint8_t stripTypeAndIncr = A1;
        static constexpr uint8_t ledNumberAndDecr = 12;
        static constexpr uint8_t animations = 4;
    } buttons;

    struct LEDs {
        static constexpr uint8_t triangleRed = 9;
        static constexpr uint8_t triangleGreen = 10;
        static constexpr uint8_t triangleBlue = 11;
        static constexpr uint8_t data = 8;
    } leds;

    struct Switches {
        static constexpr uint8_t indicatorLED = 7;
        static constexpr uint8_t mode1 = 6;
        static constexpr uint8_t mode2 = 5;
    } switches;

    struct Encoder {
        static constexpr uint8_t CW = 2;
        static constexpr uint8_t CCW = 3;
    } encoder;
};

static constexpr Pins pins;

static constexpr uint8_t outputPins[] = {
    pins.leds.data,
    pins.leds.triangleRed,
    pins.leds.triangleGreen,
    pins.leds.triangleBlue
};
static constexpr size_t outputPinsSize = sizeof(outputPins) / sizeof(outputPins[0]);

static constexpr uint8_t inputPins[] = {
    pins.pots.red, 
    pins.pots.green, 
    pins.pots.blue, 
    pins.pots.brightness, 
    pins.pots.temperature, 
    pins.pots.triangleBrightnessScaling, 
    pins.pots.stripTypeAndLEDNumber
};
static constexpr size_t inputPinsSize = sizeof(inputPins) / sizeof(inputPins[0]);

static constexpr uint8_t inputPullupPins[] = {
    pins.buttons.stripTypeAndIncr, 
    pins.buttons.ledNumberAndDecr, 
    pins.buttons.animations,
    pins.switches.indicatorLED, 
    pins.switches.mode1, 
    pins.switches.mode2, 
    pins.encoder.CW, 
    pins.encoder.CCW
};
static constexpr size_t inputPullupPinsSize = sizeof(inputPullupPins) / sizeof(inputPullupPins[0]);


static constexpr float redIndLEDScalingFactor = 0.18f;
static constexpr float greenIndLEDScalingFactor = 1.00f;
static constexpr float blueIndLEDScalingFactor = 0.18f;

class Configs
{
public:
    uint8_t ledStripCount = 10;
    uint8_t globalIndLEDScalingFactor = 100;


};

extern Configs configs;

#endif
