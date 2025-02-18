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

    ButtonState prevButtonState = this->encoderButtonState;

    if (IO.inputLevels.buttons.animations && ((this->encoderButtonState == DEPRESSED) || (this->encoderButtonState == RELEASED)))
    {
        this->encoderButtonState = PRESSED;
    }
    else if (IO.inputLevels.buttons.animations && (this->encoderButtonState == PRESSED))
    {
        this->encoderButtonState = HELD;
    }
    else if (!IO.inputLevels.buttons.animations && ((this->encoderButtonState == HELD) || (this->encoderButtonState == PRESSED)))
    {
        this->encoderButtonState = RELEASED;
    }
    else if (!IO.inputLevels.buttons.animations && (this->encoderButtonState == RELEASED))
    {
        this->encoderButtonState = DEPRESSED;
    };

    if (this->encoderButtonState != prevButtonState)
    {
        Serial.println(this->encoderButtonState);
    };




    if (!IO.inputLevels.switches.mode1 && !IO.inputLevels.switches.mode2) 
    {
        this->systemState = OFF;
    }
    else if (this->systemState == OFF) 
    {
        if (IO.inputLevels.switches.mode1)
            this->systemState = WHITE_SOLID;
        else if (IO.inputLevels.switches.mode2)
            this->systemState = COLOUR_SOLID;
    }
    else if (((this->encoderButtonState == PRESSED) || (this->encoderButtonState == HELD)) && 
            (this->systemState != WHITE_ANIMATED) && 
            (this->systemState != COLOUR_ANIMATED)) 
    {
        if (IO.inputLevels.switches.mode1)
            this->systemState = WHITE_ANIMATED;
        else if (IO.inputLevels.switches.mode2)
            this->systemState = COLOUR_ANIMATED;
    }

};
