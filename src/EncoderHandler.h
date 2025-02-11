#ifndef ENCODER_HANDLER_H
#define ENCODER_HANDLER_H

#include <Arduino.h>

class EncoderHandler {
public:
    EncoderHandler(uint8_t cwPin, uint8_t ccwPin);
    void begin();
    int getCounter();
    void resetCounter();

private:
    uint8_t cwPin;
    uint8_t ccwPin;
    volatile int counter;
    volatile uint8_t lastState;

    void handleEncoder();
    static void isrWrapper();
    static EncoderHandler* instance;
};

#endif // ENCODER_HANDLER_H
