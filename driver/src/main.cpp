#include <mouse.hpp>

int main()
{
    Mouse mouse;

    sleep(1); // let system register device

    mouse.move(1, 1);
    usleep(100000);
    // mouse.scroll(-10);

    // mouse.press(Button::Left);
    // for (int i = 0; i < 20; ++i)
    // {
    //     mouse.move(1, 1);
    //     usleep(10000);
    // }
    // mouse.release(Button::Left);

    return 0;
}