#include <Arduino.h>
#include "StateMachine.h"
#include "IOManager.h"


StateMachine stateMachine;

StateMachine::StateMachine()
{
    UpdateStates();
};

void StateMachine::UpdateStates()
{
    this->encoderButtonState = IO.inputLevels.buttons.animations ? PRESSED : RELEASED;




    SystemState prevSystemState = this->systemState;

    if (IO.inputLevels.switches.mode1 && (this->systemState == OFF))
    {
        this->systemState = WHITE_SOLID;
    }
    else if (IO.inputLevels.switches.mode2 && (this->systemState == OFF))
    {
        this->systemState = COLOUR_SOLID;
    }
    else if (!IO.inputLevels.switches.mode1 && !IO.inputLevels.switches.mode2)
    {
        this->systemState = OFF;
    }
    else if (IO.inputLevels.switches.mode1 && (this->encoderButtonState == PRESSED) && (this->systemState != WHITE_ANIMATED) && (this->systemState != COLOUR_ANIMATED))
    {
        this->systemState = WHITE_ANIMATED;
    }
    else if (IO.inputLevels.switches.mode2 && (this->encoderButtonState == PRESSED) && (this->systemState != WHITE_ANIMATED) && (this->systemState != COLOUR_ANIMATED))
    {
        this->systemState = COLOUR_ANIMATED;
    };

    if (prevSystemState != this->systemState)
    {
        Serial.println(this->systemState);
    };
};
