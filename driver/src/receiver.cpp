#include "receiver.hpp"
#include "exception.hpp"
#include "utils.hpp"

#include <unistd.h>
#include <memory>
#include <cstring>

data_unit empty_arr[DATA_SIZE] = {};

Receiver::Receiver(int fd) : curr({}), prev_data({}), epoll_fd(epoll_create1(0))
{
    struct epoll_event event;

    if (epoll_fd == -1)
    {
        throw Exception("Failed to create epoll file descriptor");
    }

    event.events = EPOLLIN;
    event.data.fd = fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event))
    {
        close(epoll_fd);

        switch (errno)
        {
        case EBADF:
            throw Exception("The epoll fd or the file descriptor to monitor is invalid");
        case EEXIST:
            throw Exception("Adding an already registered fd to the epoll instance");
        case EINVAL:
            throw Exception("One or more of the arguments passed to epoll_ctl() are invalid");
        }
    }
}

Receiver::~Receiver()
{
    if (close(epoll_fd))
    {
        log_err("Failed to close epoll file descriptor");
    }
}

bool Receiver::wait()
{
    event_count = epoll_wait(epoll_fd, events, EPOLL_EVENTS_COUNT, EPOLL_TIMEOUT);
    if (event_count == -1)
    {
        log_err("Error while waiting for epoll");
        return false;
    }

    return true;
}

bool Receiver::process()
{
    prev_data.set(curr.data);
    curr.set(empty_arr);

    data_unit buffer[DATA_SIZE];
    ssize_t bytes_read;
    for (size_t i = 0; i < event_count; i++)
    {
        bytes_read = read(events[i].data.fd, buffer, DATA_SIZE - offset);
        if (bytes_read == -1)
        {
            log_err("Error trying to read serial data");
            continue;
        }

        bool is_filled = fill(bytes_read, offset, buffer, curr.data);
        if (is_filled)
        {
            offset = 0;
            return true;
        }
    }

    return false;
}

Receiver::Data::Data() : data({})
{
}

void Receiver::Data::set(data_unit *buf)
{
    for (size_t i = 0; i < DATA_SIZE; i++)
    {
        data[i] = buf[i];
    }
}

bool Receiver::Data::is_btn_pressed(Button btn)
{
    return data[BUTTON_IDX] & btn;
}

data_unit Receiver::Data::get_x()
{
    return data[X_IDX];
}

data_unit Receiver::Data::get_y()
{
    return data[Y_IDX];
}

data_unit Receiver::Data::get_scroll()
{
    return data[SCROLL_IDX];
}

data_unit Receiver::Data::get_sensitivity()
{
    return data[SLIDER_IDX];
}

bool Receiver::is_btn_pressed(Button btn)
{
    return curr.is_btn_pressed(btn);
}

data_unit Receiver::get_x()
{
    return curr.get_x();
}

data_unit Receiver::get_y()
{
    return curr.get_y();
}

data_unit Receiver::get_scroll()
{
    return curr.get_scroll();
}

data_unit Receiver::get_sensitivity()
{
    return curr.get_sensitivity();
}

bool Receiver::has_cursor_change()
{
    return curr.get_x() != prev_data.get_x() || curr.get_y() != prev_data.get_y();
}

bool Receiver::has_scroll_change()
{
    return curr.get_scroll() != prev_data.get_scroll();
}

bool Receiver::has_sensitivity_change()
{
    return curr.get_sensitivity() != prev_data.get_sensitivity();
}

bool Receiver::has_btn_change(Button btn)
{
    return curr.is_btn_pressed(btn) != prev_data.is_btn_pressed(btn);
}
