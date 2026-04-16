#include <iostream>
#include <exception>
using namespace std;

class Exception : public exception
{
private:
    const string reason;

public:
    Exception(const string &reason);
    virtual const char *what() const throw();
};