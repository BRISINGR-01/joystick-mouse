#pragma once
#include <Arduino.h>

class RotaryEncoder
{
public:
    RotaryEncoder(int aPin, int bPin);

    void setup();
    int readVal();
};

int readAxis(int thisAxis);