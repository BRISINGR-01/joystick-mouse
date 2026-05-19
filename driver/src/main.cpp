#include <exception.hpp>
#include <receiver.hpp>
#include <data_constants.hpp>
#include <uinput_backend.hpp>
#include <mouse.hpp>
#include <utils.hpp>
#include <serial_comm.hpp>

int main(int argc, char *argv[])
{
    check_args(argc, argv);

    const string port_name = argv[1];
    int port = open_port(port_name);
    write_log("Connected to port \"" + port_name + '"');

    auto receiver = Receiver();

    try
    {
        receiver.connect(port);
    }
    catch (const std::exception &e)
    {
        close(port);
        return -1;
    }

    Mouse mouse(std::make_unique<UInputBackend>(DEVICE_NAME, VENDOR_ID, PRODUCT_ID));
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
