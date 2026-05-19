#include <exception.hpp>
#include <receiver.hpp>
#include <data_constants.hpp>
#include <uinput_backend.hpp>
#include <mouse.hpp>
#include <utils.hpp>
#include <serial_comm.hpp>

auto receiver = Receiver();
Mouse mouse(std::make_unique<UInputBackend>(DEVICE_NAME, VENDOR_ID, PRODUCT_ID));

void test_mouse()
{
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

int main(int argc, char *argv[])
{
    check_args(argc, argv);

    const string port_name = argv[1];
    int port = open_port(port_name);
    write_log("Connected to port \"" + port_name + '"');

    try
    {
        receiver.connect(port);
    }
    catch (const std::exception &e)
    {
        close(port);
        return -1;
    }

    while (true)
    {
        if (!receiver.wait())
            continue;

        try
        {
            if (!receiver.process())
                continue;
        }
        catch (const std::exception &e)
        {
            break; // device disconnected
        }

        process_data(receiver, mouse);
    }

    close(port);

    return 0;
}
