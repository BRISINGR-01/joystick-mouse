#include "receiver.hpp"
#include "exception.hpp"
#include "utils.hpp"

#include <unistd.h>
#include <memory>
#include <cstring>
#include <termios.h>

data_unit empty_arr[DATA_SIZE] = {};
data_unit buffer[DATA_SIZE] = {};
int bytes_read;
epoll_event event;

Receiver::Receiver() : curr_data({}), prev_data({})
{
}

Receiver::~Receiver()
{
    if (close(epoll_fd))
    {
        log_err("Failed to close epoll file descriptor");
    }
}

void Receiver::connect(int port)
{
    struct epoll_event event;

    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
        throw Exception("Failed to create epoll file descriptor");

    event.events = EPOLLIN;
    event.data.fd = port;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, port, &event))
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

    set_up_termios(port);
}

void set_up_termios(int port)
{
    termios tty{};
    int status = tcgetattr(port, &tty);
    if (status == -1)
        throw Exception("Could not get termios settings");

    tty.c_cc[VMIN] = 5;  /* Read at least 5 characters */
    tty.c_cc[VTIME] = 1; /* Wait for 1 *100ms = 1 second, measured in increments of 100ms */

    tty.c_cflag |= CS8                              // 8-bit characters
                   | CREAD | CLOCAL;                // Enable receiver (needed to receive input)
    tty.c_cflag &= ~(PARENB |                       // No parity
                     CSTOPB |                       // One stop bit
                     CRTSCTS);                      // Turn OFF Hardware based flow control RTS/CTS
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // Turn OFF software based flow control (XON/XOFF).
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Enable NON CANONICAL Mode for Serial Port Comm

    cfmakeraw(&tty);
    cfsetispeed(&tty, B9600); // Baud rate

    status = tcsetattr(port, TCSANOW, &tty);
    if (status == -1)
        throw Exception("Could not set termios settings");

    tcflush(port, TCIOFLUSH);
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
    prev_data.set(curr_data.data);
    curr_data.set(empty_arr);

    for (size_t i = 0; i < event_count; i++)
    {
        event = events[i];
        bytes_read = read(event.data.fd, buffer, DATA_SIZE - offset);

        switch (bytes_read)
        {
        case -1:
            log_err("Error trying to read serial data");
            break;
        case 0:
            if (event.events & (EPOLLHUP | EPOLLRDHUP))
                throw Exception("Device disconnected");
            break;
        default:
            bool is_filled = fill(bytes_read, offset, buffer, curr_data.data);
            debug(is_filled, bytes_read, offset, buffer, curr_data.data);

            if (is_filled)
            {
                offset = 0;
                return true;
            }
            offset = min(bytes_read + offset, DATA_SIZE);
            break;
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

int Receiver::Data::get_x()
{
    return data[X_IDX];
}

int Receiver::Data::get_y()
{
    return data[Y_IDX];
}

int Receiver::Data::get_scroll()
{
    return data[SCROLL_IDX];
}

int Receiver::Data::get_sensitivity()
{
    return data[SLIDER_IDX];
}

bool Receiver::is_btn_pressed(Button btn)
{
    return curr_data.is_btn_pressed(btn);
}

int Receiver::get_x()
{
    return curr_data.get_x();
}

int Receiver::get_y()
{
    return curr_data.get_y();
}

int Receiver::get_scroll()
{
    return curr_data.get_scroll();
}

int Receiver::get_sensitivity()
{
    return curr_data.get_sensitivity();
}

bool Receiver::has_cursor_change()
{
    return curr_data.get_x() != 0 || curr_data.get_y() != 0;
}

bool Receiver::has_scroll_change()
{
    return curr_data.get_scroll() != prev_data.get_scroll();
}

bool Receiver::has_btn_change()
{
    return curr_data.data[BUTTON_IDX] != prev_data.data[BUTTON_IDX];
}

bool Receiver::has_btn_change(Button btn)
{
    return curr_data.is_btn_pressed(btn) != prev_data.is_btn_pressed(btn);
}
