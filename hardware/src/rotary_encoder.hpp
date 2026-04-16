#pragma once
#include <Arduino.h>

class RotaryEncoder
{
public:
    RotaryEncoder(int aPin, int bPin);

    void setup();
    int read_and_clear();
};

int readAxis(int thisAxis);