#include <mouse.hpp>

Mouse::Mouse(std::unique_ptr<EventInterface> event_interface) : event_interface(std::move(event_interface))
{
}

void Mouse::set_sensitivity(int val)
{
    this->sensitivity = (float)val / 5;
}

void Mouse::move(int x, int y)
{
    event_interface->send_move_event(x * sensitivity, y * sensitivity);
}

void Mouse::scroll(int val)
{
    event_interface->send_scroll_event(val);
}

void Mouse::press(Button btn)
{
    event_interface->send_press_event(btn);
}

void Mouse::release(Button btn)
{
    event_interface->send_release_event(btn);
}
