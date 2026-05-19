#include <constants.hpp>
#include <data_constants.hpp>

#include <sys/epoll.h>

#define EPOLL_TIMEOUT 30000 // infinity
#define EPOLL_EVENTS_COUNT 1

void set_up_termios(int port);

class Receiver
{
    class Data
    {
    public:
        Data();
        data_unit data[DATA_SIZE];
        void set(data_unit *buf);

        bool is_btn_pressed(Button btn);
        int get_x();
        int get_y();
        int get_scroll();
        int get_sensitivity();
    };

private:
    Data prev_data;
    Data curr_data;

    int epoll_fd, offset = 0, event_count;
    struct epoll_event events[EPOLL_EVENTS_COUNT];

public:
    Receiver();
    ~Receiver();
    void connect(int port);
    bool wait();
    bool process();

    bool is_btn_pressed(Button btn);
    int get_x();
    int get_y();
    int get_scroll();
    int get_sensitivity();

    bool has_cursor_change();
    bool has_scroll_change();
    bool has_btn_change();
    bool has_btn_change(Button btn);
};
