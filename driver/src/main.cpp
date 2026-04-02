#include <uinput_backend.hpp>
#include <mouse.hpp>

#include <memory>

void test_mouse()
{
    auto uinput = std::make_unique<UInputBackend>();
    Mouse mouse(std::move(uinput));

    sleep(1); // let system register device

    mouse.move(10, 10);
    usleep(100000);
    mouse.move(30, -50);
    usleep(100000);
    mouse.scroll(5);
    usleep(100000);
    mouse.scroll(-5);
    usleep(100000);
    mouse.scroll(5);
}

int main()
{
    test_mouse();
    return 0;
}