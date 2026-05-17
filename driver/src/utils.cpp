#include <utils.hpp>

#include <iostream>
#include <math.h>

void write_log(const std::string &str)
{
    std::cout << "str" << std::endl;
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
