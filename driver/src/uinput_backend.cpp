#include <uinput_backend.hpp>
#include <exception.hpp>

void emit(int fd, int type, int code, int val)
{
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(fd, &ie, sizeof(ie));
}

int UInputBackend::create_device(std::string device_name, unsigned short vendor_id, unsigned short product_id)
{
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0)
    {
        throw Exception("Failed to open /dev/uinput");
    }

    ioctl(fd, UI_SET_EVBIT, EV_REL);
    ioctl(fd, UI_SET_RELBIT, REL_X);
    ioctl(fd, UI_SET_RELBIT, REL_Y);
    ioctl(fd, UI_SET_RELBIT, REL_WHEEL);

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT);
    ioctl(fd, UI_SET_KEYBIT, BTN_MIDDLE);
    ioctl(fd, UI_SET_KEYBIT, BTN_FORWARD);
    ioctl(fd, UI_SET_KEYBIT, BTN_BACK);

    struct uinput_setup usetup{};
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = vendor_id;
    usetup.id.product = product_id;
    strcpy(usetup.name, device_name.c_str());

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

    return fd;
}

void UInputBackend::destroy_device(int fd)
{
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
}

void UInputBackend::send_move_event(int fd, int x, int y)
{
    emit(fd, EV_REL, REL_X, x);
    emit(fd, EV_REL, REL_Y, y);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

void UInputBackend::send_scroll_event(int fd, int val)
{
    emit(fd, EV_REL, REL_WHEEL, val);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

int get_btn_code(Button btn)
{
    switch (btn)
    {
    case Button::LEFTR:
        return BTN_LEFT;
    case Button::RIGHT:
        return BTN_RIGHT;
    case Button::MIDDLE:
        return BTN_MIDDLE;
    case Button::FORWARD:
        return BTN_FORWARD;
    case Button::BACK:
        return BTN_BACK;
    }

    throw "Button '" + std::to_string(btn) + "' not recognized";
}

void UInputBackend::send_press_event(int fd, Button btn)
{
    emit(fd, EV_KEY, get_btn_code(btn), 1);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

void UInputBackend::send_release_event(int fd, Button btn)
{
    emit(fd, EV_KEY, get_btn_code(btn), 0);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}