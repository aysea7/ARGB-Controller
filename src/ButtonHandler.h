#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <Arduino.h>

class ButtonHandler {
public:
    ButtonHandler(uint8_t incPin, uint8_t decPin);
    void begin();
    void checkButtons(int &counter);

private:
    uint8_t incPin;
    uint8_t decPin;
    bool lastButtonStateInc;
    bool lastButtonStateDec;
};

#endif // BUTTON_HANDLER_H
