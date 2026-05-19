#include <joystick.hpp>

int read_axis(int axis)
{
    int reading = map(analogRead(axis), JOYSTICK_MIN, JOYSTICK_MAX, -JOYSTICK_SENSITIVITY, JOYSTICK_SENSITIVITY);

    if (abs(reading) < JOYSTICK_THRESHOLD)
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

void Joystick::update()
{
    sw.loop();
    is_pressed = sw.getState();
    x = read_axis(xPin);
    y = read_axis(yPin);
}
