#ifndef ENCODER_HANDLER_H
#define ENCODER_HANDLER_H

#include <Arduino.h>

class EncoderHandler {
public:
    EncoderHandler(uint8_t cwPin, uint8_t ccwPin, uint8_t buttonPin);
    void begin();
    void update();  

    int getCounter();
    void resetCounter();
    int getRotation();
    bool isButtonPressed();

private:
    uint8_t cwPin, ccwPin, buttonPin;
    volatile int counter;
    volatile uint8_t lastState;
    volatile int rotationDelta;
    volatile bool buttonPressed;

    void handleEncoder();
    void handleButton();

    static void isrWrapper();
    static EncoderHandler* instance;
};

#endif // ENCODER_HANDLER_H
