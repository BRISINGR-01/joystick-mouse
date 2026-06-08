#include <mouse.hpp>
#include <unistd.h>

Mouse::Mouse(std::unique_ptr<EventInterface> event_interface) : event_interface(std::move(event_interface))
{
}

void Mouse::set_sensitivity(int val)
{
    this->sensitivity = (float)val / SENSITIVITY;
}

int inline get_movement_step(int max)
{
    return std::max(1, max / MOVEMENT_STEP_PART);
}

int inline get_movement_dir(int val)
{
    return val > 0 ? 1 : -1;
}

int x_val, y_val, x_goal, y_goal, x_step, y_step;
bool x_done, y_done;
void Mouse::move(int x, int y)
{
    x_val = 0;
    x_goal = abs(x * sensitivity);
    x_step = get_movement_step(x_goal) * get_movement_dir(x);
    x_done = false;

    y_val = 0;
    y_goal = abs(y * sensitivity);
    y_step = get_movement_step(y_goal) * get_movement_dir(y);
    y_done = false;

    while (!x_done && !y_done)
    {
        if (abs(x_val) < x_goal)
        {
            x_val += x_step;
        }
        else
        {
            x_done = true;
        }

        if (abs(y_val) < y_goal)
        {
            y_val += y_step;
        }
        else
        {
            y_done = true;
        }

        event_interface->send_move_event(x_val, y_val);
        usleep(MOVEMENT_STEP_DELAY);
    }
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
