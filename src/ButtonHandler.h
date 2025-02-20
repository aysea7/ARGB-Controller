#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "Globals.h"
#include <Arduino.h>

class ButtonHandler
{
private:
    ButtonSimpleState& _currentState;
    ButtonComplexState& _currentSubstate;
    ButtonSimpleState _newState;
    ButtonComplexState _newSubstate;
    bool& _buttonDown;
    long _lastChangeTime;

    public:
    ButtonHandler(ButtonSimpleState& currentState, ButtonComplexState& currentSubstate, bool& buttonDown);
    void UpdateStates();
    ButtonSimpleState GetNewState();
    ButtonComplexState GetNewSubstate();
};

#endif
