#include <constants.hpp>
#include <data_constants.hpp>

#include <sys/epoll.h>

#define EPOLL_TIMEOUT -1 // infinity
#define EPOLL_EVENTS_COUNT 1

class Receiver
{
    class Data
    {
    public:
        Data();
        data_unit data[DATA_SIZE];
        void set(data_unit *buf);

        bool is_btn_pressed(Button btn);
        data_unit get_x();
        data_unit get_y();
        data_unit get_scroll();
        data_unit get_sensitivity();
    };

private:
    Data prev_data;
    Data curr;

    int epoll_fd, offset = 0, event_count;
    struct epoll_event events[EPOLL_EVENTS_COUNT];

public:
    Receiver(int fd);
    ~Receiver();
    bool wait();
    bool process();

    bool is_btn_pressed(Button btn);
    data_unit get_x();
    data_unit get_y();
    data_unit get_scroll();
    data_unit get_sensitivity();

    bool has_cursor_change();
    bool has_scroll_change();
    bool has_sensitivity_change();
    bool has_btn_change(Button btn);
};
