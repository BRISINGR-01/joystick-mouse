#pragma once
#include <Arduino.h>
#include <data_constants.hpp>

class RotaryEncoder
{
public:
    RotaryEncoder(int aPin, int bPin);

    void setup();
    void update();

    data_unit val = 0;
};

void handleEncoderInterrupt();