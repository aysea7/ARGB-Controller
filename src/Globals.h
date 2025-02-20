#ifndef GLOBALS_H
#define GLOBALS_H

#include "StateMachine.h"
#include "IOManager.h"
#include "ButtonHandler.h"

// Forward declarations
class StateMachine;
class IOManager;
class ButtonHandler;

// externs
extern StateMachine stateMachine;
extern IOManager IO;
extern ButtonHandler encHandler;
extern ButtonHandler incrHandler;
extern ButtonHandler decrHandler;

#endif
