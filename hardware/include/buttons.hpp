#include <data_constants.hpp>
#include <joystick.hpp>

#include <Arduino.h>
#include <ezButton.h>

class Buttons
{

public:
    Buttons(
        int left_pin,
        int right_pin,
        int middle_pin,
        int forward_pin,
        int backward_pin);
    void update();
    data_unit encode_data(Joystick &joystick);

private:
    ezButton btns[5];
};