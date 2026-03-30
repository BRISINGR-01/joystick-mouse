#include <uinput_interface.hpp>
#include <constants.hpp>

class Mouse
{
private:
    int fd;
    int sensitivity = 2;

public:
    Mouse();
    ~Mouse();

    void set_sensitivity(int val);

    void move(int x, int y);

    void scroll(int val);

    void press(Button btn);

    void release(Button btn);
};
