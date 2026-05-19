#include <serial_comm.hpp>
#include <utils.hpp>

#include <string>

void process_data(Receiver &receiver, Mouse &mouse)
{
    if (receiver.has_cursor_change())
    {
        mouse.set_sensitivity(receiver.get_sensitivity());
        mouse.move(receiver.get_x(), receiver.get_y());
    }

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
