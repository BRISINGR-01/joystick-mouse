#pragma once
#include <ezButton.h>
#include <Arduino.h>

#define JOYSITCK_SENSITIVITY 100 // output range of X or Y movement
#define JOYSITCK_MIN 0
#define JOYSITCK_MAX 1023
#define JOYSITCK_TRESHOLD JOYSITCK_SENSITIVITY / 10 // resting threshold

class Joystick
{
private:
    const int xPin;
    const int yPin;
    ezButton sw;

public:
    Joystick(int xPin, int yPin, int swPin);

    void setup();
    void loop();

    const int readX();
    const int readY();
    const int readSW();
};

int readAxis(int thisAxis);