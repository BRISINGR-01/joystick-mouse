#include <utils.hpp>
#include <exception.hpp>

#include <iostream>
#include <fcntl.h>
#include <math.h>

int open_port(const string &port_name)
{
    int port = open(port_name.c_str(), O_RDONLY | O_NOCTTY | O_NONBLOCK);
    if (port == -1)
    {
        throw new Exception("Could not open port");
    }

    return port;
}

void write_log(const std::string &str)
{
    std::cout << str << std::endl;
}

void log_err(const std::string &str)
{
    std::cerr << str << std::endl;
}

bool fill(int bytes_read, int offset, data_unit *buf, data_unit *dest)
{
    for (size_t i = offset; i < std::min(bytes_read + offset, DATA_SIZE); i++)
    {
        dest[i] = buf[i - offset];
    }

    return offset + bytes_read >= DATA_SIZE;
}

void debug(bool is_filled, int bytes_read, int offset, data_unit *buf, data_unit *curr)
{
    printf("filled: %s, bytes: %d, offset: %d\n", is_filled ? "true" : "false", bytes_read, offset);
    printf("buffer: ");
    for (size_t i = 0; i < DATA_SIZE; i++)
    {
        printf("%d ", (int)buf[i]);
    }
    printf("\ndata  : ");
    for (size_t i = 0; i < DATA_SIZE; i++)
    {
        printf("%d ", (int)curr[i]);
    }
    printf("\n");
}

std::string get_btn_debug(int btn_idx)
{
    switch (btn_idx)
    {
    case LEFT_IDX:
        return "LEFT";
    case RIGHT_IDX:
        return "RIGHT";
    case MIDDLE_IDX:
        return "MIDDLE";
    case FORWARD_IDX:
        return "FORWARD";
    case BACKWARD_IDX:
        return "BACKWARD";
    }

    return std::to_string(btn_idx);
}