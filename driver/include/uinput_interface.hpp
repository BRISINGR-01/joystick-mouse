#include <linux/uinput.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include <constants.hpp>

static void emit(int fd, int type, int code, int val);

namespace uinput_interface
{
    int create_device(std::string device_name, unsigned short vendor_id, unsigned short product_id);

    void destroy_device(int fd);

    void send_move_event(int fd, int x, int y);
    void send_scroll_event(int fd, int val);
    void send_press_event(int fd, Button btn);
    void send_release_event(int fd, Button btn);
}