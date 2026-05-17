#include <buttons.hpp>

Buttons::Buttons(int left_pin, int right_pin, int middle_pin, int forward_pin, int backward_pin) : btns({
                                                                                                       ezButton(left_pin, INPUT_PULLUP),
                                                                                                       ezButton(right_pin, INPUT_PULLUP),
                                                                                                       ezButton(middle_pin, INPUT_PULLUP),
                                                                                                       ezButton(forward_pin, INPUT_PULLUP),
                                                                                                       ezButton(backward_pin, INPUT_PULLUP),
                                                                                                   })
{
}

void Buttons::update()
{
    for (auto &btn : btns)
    {
        btn.loop();
    }
}

data_unit Buttons::encode_data(Joystick &joystick)
{
    data_unit state = 0;
    for (size_t i = 0; i < BUTTON_COUNT; i++)
    {
        state |= (btns[i].getState() << i);
    }
    if (joystick.is_pressed)
    {
        state |= Button::MIDDLE;
    }

    return state;
}
