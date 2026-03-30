#include <systemd/sd-device.h>
#include <systemd/sd-event.h>
#include <stdio.h>
#include <string.h>

static int device_handler(sd_device_monitor *m, sd_device *dev, void *userdata)
{
    const char *action = nullptr;
    const char *subsystem = nullptr;

    sd_device_get_action(dev, &action);
    sd_device_get_subsystem(dev, &subsystem);

    if (!action || !subsystem)
        return 0;

    // Only care about USB devices
    if (strcmp(subsystem, "usb") != 0)
        return 0;

    if (strcmp(action, "add") == 0)
    {
        const char *vid = nullptr;
        const char *pid = nullptr;

        sd_device_get_sysattr_value(dev, "idVendor", &vid);
        sd_device_get_sysattr_value(dev, "idProduct", &pid);

        printf("USB device added: VID=%s PID=%s\n",
               vid ? vid : "?", pid ? pid : "?");
    }

    return 0;
}

int main()
{
    sd_device_monitor *mon = nullptr;
    sd_event *event = nullptr;

    // Create monitor
    sd_device_monitor_new(&mon);
    sd_device_monitor_filter_add_match_subsystem_devtype(mon, "usb", nullptr);
    sd_device_monitor_start(mon, device_handler, nullptr);

    // Create event loop
    sd_event_default(&event);

    // Attach monitor to event loop
    sd_device_monitor_attach_event(mon, event);

    // Run loop forever
    sd_event_loop(event);

    return 0;
}