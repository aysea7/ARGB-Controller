#include "Config.h"
#include <Arduino.h>
#include "Globals.h"

Configs configs;

Configs::Configs()
{
    leds = new CRGB[ledStripCount]; // Dynamically allocate array
};

Configs::~Configs()
{
    delete[] leds; // Free memory on destruction
};
