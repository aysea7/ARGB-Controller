#include "EncoderHandler.h"

EncoderHandler* EncoderHandler::instance = nullptr;

EncoderHandler::EncoderHandler(uint8_t cwPin, uint8_t ccwPin, uint8_t buttonPin)
    : cwPin(cwPin), ccwPin(ccwPin), buttonPin(buttonPin),
      counter(0), lastState(0), rotationDelta(0), buttonPressed(false) {}

void EncoderHandler::begin() {
    pinMode(cwPin, INPUT_PULLUP);
    pinMode(ccwPin, INPUT_PULLUP);
    pinMode(buttonPin, INPUT_PULLUP);

    instance = this;
    lastState = (digitalRead(cwPin) << 1) | digitalRead(ccwPin);

    attachInterrupt(digitalPinToInterrupt(cwPin), isrWrapper, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ccwPin), isrWrapper, CHANGE);
}

void EncoderHandler::isrWrapper() {
    if (instance) {
        instance->handleEncoder();
    }
}

void EncoderHandler::handleEncoder() {
    static unsigned long lastInterruptTime = 0;
    unsigned long interruptTime = millis();

    if (interruptTime - lastInterruptTime < 3) {  
        return;
    }
    lastInterruptTime = interruptTime;

    uint8_t state = (digitalRead(cwPin) << 1) | digitalRead(ccwPin);

    if ((lastState == 0b00 && state == 0b01) || 
        (lastState == 0b01 && state == 0b11) || 
        (lastState == 0b11 && state == 0b10) || 
        (lastState == 0b10 && state == 0b00)) {
        rotationDelta = 1;  // CW rotation
    } 
    else if ((lastState == 0b00 && state == 0b10) || 
             (lastState == 0b10 && state == 0b11) || 
             (lastState == 0b11 && state == 0b01) || 
             (lastState == 0b01 && state == 0b00)) {
        rotationDelta = -1;  // CCW rotation
    }

    lastState = state;
}

void EncoderHandler::handleButton() {
    buttonPressed = !digitalRead(buttonPin);  // LOW = pressed
}

void EncoderHandler::update() {
    handleButton();
}

int EncoderHandler::getCounter() {
    noInterrupts();
    int tempCounter = counter;
    interrupts();
    return tempCounter;
}

void EncoderHandler::resetCounter() {
    noInterrupts();
    counter = 0;
    interrupts();
}

int EncoderHandler::getRotation() {
    noInterrupts();
    int tempRotation = rotationDelta;
    rotationDelta = 0;  // Reset after reading
    interrupts();
    
    return (tempRotation > 0) ? 1 : (tempRotation < 0) ? -1 : 0;  // Ensure only ±1 step per read
}



bool EncoderHandler::isButtonPressed() {
    return buttonPressed;
}
