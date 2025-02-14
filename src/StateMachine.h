#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>


enum SystemState {
    OFF,
    WHITE_SOLID,
    WHITE_ANIMATED,
    COLOUR_SOLID,
    COLOUR_ANIMATED
};

enum SetupSubstate {
    NO_SETUP,
    STRIP_TYPE,
    LED_COUNT
};

enum ButtonState {
    PRESSED,
    RELEASED
};

class StateMachine
{

};

extern StateMachine stateMachine;

#endif