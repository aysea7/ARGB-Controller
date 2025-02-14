#include <Arduino.h>
#include "EncoderHandler.h"
#include "ButtonHandler.h"
#include "Config.h"
#include "Setup.h"
#include "IOManager.h"
#include "LEDTriangle.h"
#include "StateMachine.h"


#include <FastLED.h>

#define NUM_LEDS 26    // Number of LEDs in the strip
#define LED_TYPE WS2812B // Change to your LED type if different
#define COLOR_ORDER GRB  // Change if your strip has a different order

uint8_t stripBrightness = 255;

CRGB leds[NUM_LEDS];


EncoderHandler encoder(pins.encoder.CW, pins.encoder.CCW, pins.buttons.animations);


void setup() {

  encoder.begin();


  Serial.begin(9600);
  
  SetPinMode(inputPins, inputPinsSize, INPUT);
  SetPinMode(inputPullupPins, inputPullupPinsSize, INPUT_PULLUP);
  SetPinMode(outputPins, outputPinsSize, OUTPUT);


  FastLED.addLeds<LED_TYPE, pins.leds.data, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(stripBrightness);
}

unsigned long previousMillis = 0;
unsigned long animationInterval = 1; // Update interval

int i = 0;  // Current hue shift step

void loop() {
    IO.PollInputs();
    IO.UpdateOutputLevels();
    SendPWMToTriangle();

    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(IO.inputLevels.pots.red, IO.inputLevels.pots.green, IO.inputLevels.pots.blue);
    }
    FastLED.setBrightness(IO.inputLevels.pots.brightness);
    FastLED.show();

    /* encoder.update();  

    static int lastRotation = 0;
    int rotation = encoder.getRotation();
    bool buttonHeld = encoder.isButtonPressed();

    if (buttonHeld && rotation != 0 && rotation != lastRotation) {  
        animationInterval += (rotation > 0) ? 1 : -1;  // Adjust delay smoothly
        animationInterval = constrain(animationInterval, 1, 500);
        
        Serial.print("New Delay: ");
        Serial.println(animationInterval);
        
        lastRotation = rotation;  // Store last rotation to prevent repeats
    } else if (rotation == 0) {
        lastRotation = 0;  // Reset when no rotation detected
    }


    FastLED.setBrightness(IO.inputLevels.pots.brightness);

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= animationInterval) {
        previousMillis = currentMillis;

        // Update LEDs one step per loop iteration
        for (int j = 0; j < NUM_LEDS; j++) {
            leds[j] = CHSV((i + (j * 10)) % 256, 255, 255);
        }
        FastLED.show();

        // Increment i, and reset after reaching 256
        i++;
        if (i >= 256) {
            i = 0;
        }
    } */
}
