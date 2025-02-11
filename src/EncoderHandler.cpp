#include "EncoderHandler.h"

EncoderHandler* EncoderHandler::instance = nullptr;  // Static instance

EncoderHandler::EncoderHandler(uint8_t cwPin, uint8_t ccwPin)
    : cwPin(cwPin), ccwPin(ccwPin), counter(0), lastState(0) {}

void EncoderHandler::begin() {
    pinMode(cwPin, INPUT_PULLUP);
    pinMode(ccwPin, INPUT_PULLUP);

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

    if (interruptTime - lastInterruptTime < 3) {  // Debounce (3ms)
        return;
    }
    lastInterruptTime = interruptTime;

    uint8_t state = (digitalRead(cwPin) << 1) | digitalRead(ccwPin);

    if ((lastState == 0b00 && state == 0b01) || 
        (lastState == 0b01 && state == 0b11) || 
        (lastState == 0b11 && state == 0b10) || 
        (lastState == 0b10 && state == 0b00)) {
        counter++;
    } else if ((lastState == 0b00 && state == 0b10) || 
               (lastState == 0b10 && state == 0b11) || 
               (lastState == 0b11 && state == 0b01) || 
               (lastState == 0b01 && state == 0b00)) {
        counter--;
    }

    lastState = state;
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
