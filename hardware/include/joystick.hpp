#pragma once
#include <ezButton.h>
#include <Arduino.h>
#include <data_constants.hpp>

#define JOYSTICK_SENSITIVITY 100 // output range of X or Y movement (must fit in a single signed byte, so between -127 and 127)
#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 1023
#define JOYSTICK_THRESHOLD JOYSTICK_SENSITIVITY / 10 // resting threshold

class Joystick
{
private:
    const int xPin;
    const int yPin;
    ezButton sw;

public:
    Joystick(int xPin, int yPin, int swPin);

    void setup();
    void update(); // must be run every loop
    bool has_input();

    data_unit x;
    data_unit y;
    bool is_pressed;
};

int read_axis(int thisAxis);