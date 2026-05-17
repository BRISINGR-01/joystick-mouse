#pragma once
#include <constants.hpp>
#include <event_interface.hpp>

#include <linux/uinput.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

/**
 * @brief Map a Button enum to its corresponding Linux input code.
 *
 * @param btn Button enum value
 * @return int Linux input code (e.g., BTN_LEFT, BTN_RIGHT)
 */
int get_btn_code(Button btn);

/**
 * @class UInputBackend
 * @brief uinput implementation for EventInterface
 *
 * Provides a high-level API to control a virtual mouse device:
 * movement, scrolling, and button actions.
 */
class UInputBackend : public EventInterface
{
private:
    /// File descriptor for `/dev/uinput` (virtual device handle)
    int fd;

    /**
     * @brief Emit a single input event to the device.
     *
     * @param type Event type (e.g., EV_REL, EV_KEY)
     * @param code Event code (e.g., REL_X, BTN_LEFT)
     * @param val Event value
     */
    void emit(int type, int code, int val);

public:
    /**
     * @brief Create a virtual uinput device.
     *
     * Configures movement axes, buttons, and sets device metadata.
     *
     * @param device_name Name of the virtual device
     * @param vendor_id USB vendor ID to assign
     * @param product_id USB product ID to assign
     */
    UInputBackend(std::string device_name, unsigned short vendor_id, unsigned short product_id);

    /// @brief Destroy device
    ~UInputBackend();

    /**
     * @brief Send relative mouse movement events.
     *
     * @param x Relative movement along X axis
     * @param y Relative movement along Y axis
     */
    void send_move_event(int x, int y) override;

    /**
     * @brief Send scroll wheel events.
     *
     * @param val Scroll amount (positive = up, negative = down)
     */
    void send_scroll_event(int val) override;

    /**
     * @brief Send a button press event.
     *
     * @param btn Button to press
     */
    void send_press_event(Button btn) override;

    /**
     * @brief Send a button release event.
     *
     * @param btn Button to release
     */
    void send_release_event(Button btn) override;
};
