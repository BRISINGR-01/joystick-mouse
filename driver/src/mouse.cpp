#include <mouse.hpp>
#include <unistd.h>

Mouse::Mouse(std::unique_ptr<EventInterface> event_interface) : event_interface(std::move(event_interface))
{
}

void Mouse::set_sensitivity(int val)
{
    // this->sensitivity = (float)val / 5;
    this->sensitivity = 0.1;
}

int get_step(int max)
{
    return std::max(1, max / 5);
}

int x_val, y_val, x_end, y_end, x_step, y_step;
bool x_done, y_done;
void Mouse::move(int x, int y)
{
    x_val = 0;
    x_end = abs(x * sensitivity);
    x_step = get_step(x_end) * (x > 0 ? 1 : -1);
    x_done = false;

    y_val = 0;
    y_end = abs(y * sensitivity);
    y_step = get_step(y_end) * (y > 0 ? 1 : -1);
    y_done = false;

    while (!x_done || !y_done)
    {
        if (abs(x_val) < x_end)
        {
            x_val += x_step;
        }
        else
        {
            x_done = true;
        }

        if (abs(y_val) < y_end)
        {
            y_val += y_step;
        }
        else
        {
            y_done = true;
        }

        event_interface->send_move_event(x_val, y_val);
        usleep(100);
    }
    printf("move: %d %d\n", x_end * (x > 0 ? 1 : -1), y_end * (y > 0 ? 1 : -1));
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
