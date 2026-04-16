#include <exception.hpp>

Exception::Exception(const string &reason) : reason(reason)
{
}

const char *Exception::what() const throw()
{
    return this->reason.c_str();
}
