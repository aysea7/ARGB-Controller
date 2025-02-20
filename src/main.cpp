#include "Globals.h"
#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "Setup.h"
#include "LEDTriangle.h"

#define NUM_LEDS 26      // Number of LEDs in the strip
#define LED_TYPE WS2812B // Change to your LED type if different
#define COLOR_ORDER GRB  // Change if your strip has a different order

uint8_t stripBrightness = 255;

void setup()
{
    Serial.begin(9600);

    SetPinMode(inputPins, inputPinsSize, INPUT);
    SetPinMode(inputPullupPins, inputPullupPinsSize, INPUT_PULLUP);
    SetPinMode(outputPins, outputPinsSize, OUTPUT);

    FastLED.addLeds<LED_TYPE, pins.leds.data, COLOR_ORDER>(configs.leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(stripBrightness);
}

unsigned long previousMillis = 0;
unsigned long animationInterval = 25; // Update interval

int i = 0; // Current hue shift step

void loop()
{
    IO.PollInputs();
    stateMachine.UpdateStates();

    if (stateMachine.systemState == COLOUR_SOLID)
    {

        for (int i = 0; i < NUM_LEDS; i++)
        {
            configs.leds[i] = CRGB(IO.inputLevels.pots.red, IO.inputLevels.pots.green, IO.inputLevels.pots.blue);
        }
        FastLED.setBrightness(IO.inputLevels.pots.brightness);
        FastLED.show();
    }
    else if (stateMachine.systemState == COLOUR_ANIMATED)
    {

        FastLED.setBrightness(IO.inputLevels.pots.brightness);

        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= animationInterval)
        {
            previousMillis = currentMillis;

            // Update LEDs one step per loop iteration
            for (int j = 0; j < NUM_LEDS; j++)
            {
                configs.leds[j] = CHSV((i + (j * 10)) % 256, 255, 255);
            }
            FastLED.show();
            

            // Increment i, and reset after reaching 256
            i++;
            if (i >= 256)
            {
                i = 0;
            }
        }
    }
    else
    {
        FastLED.clear();
        FastLED.show();
    }
    IO.UpdateOutputLevels();
    SendPWMToTriangle();
}
