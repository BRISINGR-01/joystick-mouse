#include <exception.hpp>
#include <utils.hpp>

Exception::Exception(const string &reason) : reason(reason)
{
    log_err(reason);
}

const char *Exception::what() const throw()
{
    return this->reason.c_str();
}
