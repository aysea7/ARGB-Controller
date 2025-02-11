#include "Config.h"
#include <Arduino.h>

void SetPinMode(const uint8_t *pinArray, const size_t arraySize, uint8_t mode)
{
    for(size_t i = 0; i < arraySize; i++){
        pinMode(pinArray[i], mode);
    }
};

void InitFastLED()
{

};