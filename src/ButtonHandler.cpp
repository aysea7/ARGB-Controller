#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(uint8_t incPin, uint8_t decPin)
    : incPin(incPin), decPin(decPin), lastButtonStateInc(HIGH), lastButtonStateDec(HIGH) {}

void ButtonHandler::begin() {
    pinMode(incPin, INPUT_PULLUP);
    pinMode(decPin, INPUT_PULLUP);
}

void ButtonHandler::checkButtons(int &counter) {
    bool buttonStateInc = digitalRead(incPin);
    bool buttonStateDec = digitalRead(decPin);

    if (buttonStateInc == LOW && lastButtonStateInc == HIGH) {
        counter++;
        Serial.println("Button Increment Pressed → Counter: " + String(counter));
    }

    if (buttonStateDec == LOW && lastButtonStateDec == HIGH) {
        counter--;
        Serial.println("Button Decrement Pressed → Counter: " + String(counter));
    }

    lastButtonStateInc = buttonStateInc;
    lastButtonStateDec = buttonStateDec;
}
