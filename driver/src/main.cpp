#include <receiver.hpp>
#include <data_constants.hpp>
#include <uinput_backend.hpp>
#include <mouse.hpp>
#include <utils.hpp>

#include <fstream>
#include <ostream>
#include <iostream>

Mouse mouse(std::make_unique<UInputBackend>(DEVICE_NAME, VENDOR_ID, PRODUCT_ID));

void test_mouse()
{
    mouse.move(10, 10);
    usleep(100000);
    mouse.move(30, -50);
    usleep(100000);
    mouse.scroll(5);
    usleep(100000);
    mouse.scroll(-5);
    usleep(100000);
    mouse.scroll(5);
}

Button get_btn(int btn_idx)
{
    switch (btn_idx)
    {
    case LEFT_IDX:
        return Button::LEFT;
    case RIGHT_IDX:
        return Button::RIGHT;
    case MIDDLE_IDX:
        return Button::MIDDLE;
    case FORWARD_IDX:
        return Button::FORWARD;
    case BACKWARD_IDX:
        return Button::BACKWARD;
    }

    log_err(("Button '" + std::to_string(btn_idx) + "' not recognized").c_str());
    return (Button)-1;
}

void on_data_received(Receiver &receiver)
{
    if (receiver.has_cursor_change())
    {
        mouse.set_sensitivity(receiver.get_sensitivity());
        mouse.move(receiver.get_x(), receiver.get_y());
    }

    if (receiver.has_scroll_change())
    {
        mouse.scroll(receiver.get_scroll());
    }

    bool is_pressed;
    Button btn;
    for (size_t btn_idx = 0; btn_idx < BUTTON_COUNT; btn_idx++)
    {
        btn = get_btn(btn_idx);
        if (btn == -1)
            continue;

        if (receiver.has_btn_change(btn))
        {
            is_pressed = receiver.is_btn_pressed(btn);
            if (is_pressed)
            {
                mouse.press(btn);
            }
            else
            {
                mouse.release(btn);
            }
        }
    }
}

int main()
{
    int port = open("/dev/ttyUSB0", O_RDONLY);
    if (port == -1)
    {
        log_err("Could not open port");
        return 1;
    }

    Receiver receiver(port);

    while (1)
    {
        if (!receiver.wait())
        {
            continue;
        }

        if (!receiver.process())
        {
            continue;
        }

        on_data_received(receiver);
    }
}
