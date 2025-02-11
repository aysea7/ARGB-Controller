#include <Arduino.h>
#include "EncoderHandler.h"
#include "ButtonHandler.h"
#include "Config.h"
#include "Setup.h"
#include "IOManager.h"
#include "LEDTriangle.h"


#include <FastLED.h>

#define NUM_LEDS 26    // Number of LEDs in the strip
#define LED_TYPE WS2812B // Change to your LED type if different
#define COLOR_ORDER GRB  // Change if your strip has a different order

uint8_t stripBrightness = 255;

CRGB leds[NUM_LEDS];


void setup() {
  Serial.begin(9600);
  
  SetPinMode(inputPins, inputPinsSize, INPUT);
  SetPinMode(inputPullupPins, inputPullupPinsSize, INPUT_PULLUP);
  SetPinMode(outputPins, outputPinsSize, OUTPUT);


  FastLED.addLeds<LED_TYPE, pins.leds.data, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(stripBrightness);
}

void loop() {
  IO.PollInputs();
  IO.UpdateOutputLevels();
  SendPWMToTriangle();

    /* for(int i = 0; i < 256; i++) {
        for(int j = 0; j < NUM_LEDS; j++) {
            stripBrightness = analogRead(pins.pots.brightness) >> 2;
            FastLED.setBrightness(stripBrightness);
            leds[j] = CHSV((i + (j * 10)) % 256, 255, 255);
        }
        FastLED.show();
        delay(20);
    } */







  bool switchOn = digitalRead(pins.switches.indicatorLED);

  int redValue = switchOn ? analogRead(pins.pots.red) : 0;
  int greenValue = switchOn ? analogRead(pins.pots.green) : 0;
  int blueValue = switchOn ? analogRead(pins.pots.blue) : 0;

  


  //globalIndLEDScalingFactor = analogRead(trimPotTriangleBrightnessScalingFactorPin) / 1023.0f;

  //analogWrite(LEDIndicatorRedPin, ((uint8_t)(redValue * redIndLEDScalingFactor * globalIndLEDScalingFactor / 4)));
  //analogWrite(LEDIndicatorGreenPin, ((uint8_t)(greenValue * greenIndLEDScalingFactor * globalIndLEDScalingFactor / 4)));
  //analogWrite(LEDIndicatorBluePin, ((uint8_t)(blueValue * blueIndLEDScalingFactor * globalIndLEDScalingFactor / 4)));
}