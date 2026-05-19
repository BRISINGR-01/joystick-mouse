#include <exception.hpp>
#include <receiver.hpp>
#include <data_constants.hpp>
#include <uinput_backend.hpp>
#include <mouse.hpp>
#include <utils.hpp>

auto receiver = Receiver();
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

void on_data_received();
void listen_to(string port_name);

int main()
{
    string port_name = "/dev/ttyUSB0";
    try
    {
        listen_to(port_name);
    }
    catch (const std::exception &)
    {
    }
}

void listen_to(string port_name)
{
    int port = open_port(port_name);
    write_log("Connected to port \"" + port_name + '"');

    try
    {
        receiver.connect(port);
    }
    catch (const std::exception &e)
    {
        close(port);
        return;
    }

    while (true)
    {
        if (!receiver.wait())
            continue;

        try
        {
            if (!receiver.process())
                continue;
        }
        catch (const std::exception &e)
        {
            break;
        }

        on_data_received();
    }

    close(port);
}

void on_data_received()
{
    if (receiver.has_cursor_change())
    {
        mouse.set_sensitivity(receiver.get_sensitivity());
        mouse.move(receiver.get_x(), receiver.get_y());
    }

    return;

    if (receiver.has_scroll_change())
    {
        mouse.scroll(receiver.get_scroll());
        printf("scroll: %d\n", receiver.get_scroll());
    }

    if (!receiver.has_btn_change())
        return;

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
                printf("press: %s\n", get_btn_debug(btn).c_str());
            }
            else
            {
                mouse.release(btn);
                printf("release: %s\n", get_btn_debug(btn).c_str());
            }
        }
    }
}
