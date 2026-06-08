#include <exception.hpp>
#include <receiver.hpp>
#include <data_constants.hpp>
#include <uinput_backend.hpp>
#include <mouse.hpp>
#include <utils.hpp>
#include <serial_comm.hpp>

int main()
{
    char *dev_name = std::getenv("DEVNAME");
    if (dev_name == NULL)
    {
        log_err("No port was provided");
        exit(-1);
    }

    const string port_name = dev_name;

    int port = open_port(port_name);

    auto receiver = Receiver();
    try
    {
        receiver.connect(port);
    }
    catch (const std::exception &e)
    {
        close(port);
        exit(-1);
    }

    Mouse mouse(std::make_unique<UInputBackend>(DEVICE_NAME, VENDOR_ID, PRODUCT_ID));
    while (true)
    {
        if (!receiver.wait())
            continue;

        switch (receiver.process())
        {
        case Receiver::Status::OK:
            process_data(receiver, mouse);
            break;
        case Receiver::Status::NoAction:
            break;
        case Receiver::Status::Disconnected:
            write_log("Device disconnected");
            break;
        }
    }

    close(port);

    return 0;
}
