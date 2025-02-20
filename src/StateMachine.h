#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Globals.h"
#include <Arduino.h>

enum SystemState {
    OFF,
    WHITE_SOLID,
    WHITE_ANIMATED,
    COLOUR_SOLID,
    COLOUR_ANIMATED
};

enum SetupState {
    NO_SETUP,
    STRIP_TYPE,
    LED_COUNT
};

enum ButtonSimpleState {
    PRESS_TRANSIENT,
    PRESSED,
    RELEASE_TRANSIENT,
    RELEASED
};

enum ButtonComplexState {
    NONE,
    HELD,
    DOUBLE_CLICKED,
    DOUBLE_CLICKED_AND_HELD
};

enum SwitchState {
    DISABLED,
    ENABLED
};

class StateMachine
{
    private:
        void UpdateSystemState();
        void UpdateButtonStates();

    public:
        SystemState systemState;
        SetupState setupState;
        ButtonSimpleState encoderButtonState;
        ButtonComplexState encoderButtonSubstate = NONE;
        ButtonSimpleState incrButtonState;
        ButtonComplexState incrButtonSubstate = NONE;
        ButtonSimpleState decrButtonState;
        ButtonComplexState decrButtonSubstate = NONE;
        SwitchState debugState;
        SwitchState triangleState;

        void UpdateStates();
};

#endif