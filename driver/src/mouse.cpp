#include <mouse.hpp>

Mouse::Mouse()
{
    this->fd = uinput_interface::create_device(DEVICE_NAME, VENDOR_ID, PRODUCT_ID);
}

Mouse::~Mouse()
{
    uinput_interface::destroy_device(this->fd);
}

void Mouse::set_sensitivity(int val)
{
    this->sensitivity = val;
}

void Mouse::move(int x, int y)
{
    uinput_interface::send_move_event(this->fd, x * sensitivity, y * sensitivity);
}

void Mouse::scroll(int val)
{
    uinput_interface::send_scroll_event(this->fd, val);
}

void Mouse::press(Button btn)
{
    uinput_interface::send_press_event(this->fd, btn);
}

void Mouse::release(Button btn)
{
    uinput_interface::send_release_event(this->fd, btn);
}
