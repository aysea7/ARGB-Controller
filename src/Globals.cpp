#include "Globals.h"

// Global instances
StateMachine stateMachine;
IOManager IO;

// Button handlers
ButtonHandler encHandler(stateMachine.encoderButtonState, stateMachine.encoderButtonSubstate, IO.inputLevels.buttons.animations);
ButtonHandler incrHandler(stateMachine.incrButtonState, stateMachine.incrButtonSubstate, IO.inputLevels.buttons.stripTypeAndIncr);
ButtonHandler decrHandler(stateMachine.decrButtonState, stateMachine.decrButtonSubstate, IO.inputLevels.buttons.ledNumberAndDecr);
