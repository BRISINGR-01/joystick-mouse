#include <mouse.hpp>

Mouse::Mouse(std::unique_ptr<EventInterface> ei) : ei(std::move(ei))
{
    this->fd = this->ei->create_device(DEVICE_NAME, VENDOR_ID, PRODUCT_ID);
}

Mouse::~Mouse()
{
    ei->destroy_device(this->fd);
}

void Mouse::set_sensitivity(int val)
{
    this->sensitivity = val;
}

void Mouse::move(int x, int y)
{
    ei->send_move_event(this->fd, x * sensitivity, y * sensitivity);
}

void Mouse::scroll(int val)
{
    ei->send_scroll_event(this->fd, val);
}

void Mouse::press(Button btn)
{
    ei->send_press_event(this->fd, btn);
}

void Mouse::release(Button btn)
{
    ei->send_release_event(this->fd, btn);
}
