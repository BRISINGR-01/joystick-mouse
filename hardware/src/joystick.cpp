#include <joystick.hpp>

int readAxis(int axis)
{
    int reading = analogRead(axis);
    reading = map(reading, JOYSITCK_MIN, JOYSITCK_MAX, -JOYSITCK_SENSITIVITY, JOYSITCK_SENSITIVITY);

    if (abs(reading) < JOYSITCK_TRESHOLD)
    {
        reading = 0;
    }

    return reading;
}

Joystick::Joystick(int xPin, int yPin, int swPin) : xPin(xPin), yPin(yPin), sw(ezButton(swPin, INPUT_PULLUP))
{
}

void Joystick::setup()
{
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    sw.setDebounceTime(50);
}

void Joystick::loop()
{
    sw.loop();
}

const int Joystick::readX()
{
    return readAxis(xPin);
}

const int Joystick::readY()
{
    return readAxis(yPin);
}

const int Joystick::readSW()
{
    return sw.getState();
}
