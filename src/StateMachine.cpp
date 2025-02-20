#include "Globals.h"
#include <Arduino.h>

void StateMachine::UpdateSystemState()
{
    if (!IO.inputLevels.switches.mode1 && !IO.inputLevels.switches.mode2) 
    {
        this->systemState = OFF;
    }
    else if (this->systemState == OFF) 
    {
        this->systemState = IO.inputLevels.switches.mode1 ? WHITE_SOLID : COLOUR_SOLID;
    }
    else if ((this->encoderButtonState == PRESS_TRANSIENT || this->encoderButtonState == PRESSED) && 
             (this->systemState != WHITE_ANIMATED && this->systemState != COLOUR_ANIMATED)) 
    {
        this->systemState = IO.inputLevels.switches.mode1 ? WHITE_ANIMATED : COLOUR_ANIMATED;
    }
}

void StateMachine::UpdateButtonStates()
{
    ButtonComplexState old = this-> encoderButtonSubstate;
    
    encHandler.UpdateStates();
    this->encoderButtonState = encHandler.GetNewState();
    this->encoderButtonSubstate = encHandler.GetNewSubstate();

    incrHandler.UpdateStates();
    this->incrButtonState = incrHandler.GetNewState();
    this->incrButtonSubstate = incrHandler.GetNewSubstate();

    decrHandler.UpdateStates();
    this->decrButtonState = decrHandler.GetNewState();
    this->decrButtonSubstate = decrHandler.GetNewSubstate();

    if (old != this->encoderButtonSubstate)
    {
        Serial.println(this->encoderButtonSubstate);
    };
}

void StateMachine::UpdateStates()
{
    this->triangleState = (SwitchState)(IO.inputLevels.switches.indicatorLED && ((this->systemState == COLOUR_SOLID) || (this->systemState == COLOUR_ANIMATED)));
    UpdateButtonStates();
    UpdateSystemState();
}

