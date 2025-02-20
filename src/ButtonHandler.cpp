#include "ButtonHandler.h"
#include "Globals.h"
#include <Arduino.h>

ButtonHandler::ButtonHandler(ButtonSimpleState& currentState, ButtonComplexState& currentSubstate, bool& buttonDown)
    : _currentState(currentState), _currentSubstate(currentSubstate), _buttonDown(buttonDown){};

void ButtonHandler::UpdateStates()
{
    if (_buttonDown && ((_currentState == RELEASE_TRANSIENT) || (_currentState == RELEASED)))
    {
        _newState = PRESS_TRANSIENT;
    }
    else if (_buttonDown && (_currentState == PRESS_TRANSIENT))
    {
        _newState = PRESSED;
    }
    else if (!_buttonDown && ((_currentState == PRESS_TRANSIENT) || (_currentState == PRESSED)))
    {
        _newState = RELEASE_TRANSIENT;
    }
    else if (!_buttonDown && (_currentState == RELEASE_TRANSIENT))
    {
        _newState = RELEASED;
    };
};

ButtonSimpleState ButtonHandler::GetNewState()
{
    return _newState;
};

ButtonComplexState ButtonHandler::GetNewSubstate()
{
    return _newSubstate;
};
