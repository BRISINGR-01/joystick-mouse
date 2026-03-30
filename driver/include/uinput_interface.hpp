#pragma once

#include <linux/uinput.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include <constants.hpp>

/**
 * @brief Emit a single input event to the virtual device.
 *
 * @param fd File descriptor of the uinput device
 * @param type Event type (e.g., EV_REL, EV_KEY)
 * @param code Event code (e.g., REL_X, BTN_LEFT)
 * @param val Event value
 */
static void emit(int fd, int type, int code, int val);

/**
 * @brief Map a Button enum to its corresponding Linux input code.
 *
 * @param btn Button enum value
 * @return int Linux input code (e.g., BTN_LEFT, BTN_RIGHT)
 */
static int get_btn_code(Button btn);

namespace uinput_interface
{
    /**
     * @brief Create a virtual uinput device.
     *
     * Configures movement axes, buttons, and sets device metadata.
     *
     * @param device_name Name of the virtual device
     * @param vendor_id USB vendor ID to assign
     * @param product_id USB product ID to assign
     * @return int File descriptor of the created uinput device
     */
    int create_device(std::string device_name, unsigned short vendor_id, unsigned short product_id);

    /**
     * @brief Destroy a virtual uinput device.
     *
     * @param fd File descriptor of the device to destroy
     */
    void destroy_device(int fd);

    /**
     * @brief Send relative mouse movement events.
     *
     * @param fd File descriptor of the virtual device
     * @param x Relative movement along X axis
     * @param y Relative movement along Y axis
     */
    void send_move_event(int fd, int x, int y);

    /**
     * @brief Send scroll wheel events.
     *
     * @param fd File descriptor of the virtual device
     * @param val Scroll amount (positive = up, negative = down)
     */
    void send_scroll_event(int fd, int val);

    /**
     * @brief Send a button press event.
     *
     * @param fd File descriptor of the virtual device
     * @param btn Button to press
     */
    void send_press_event(int fd, Button btn);

    /**
     * @brief Send a button release event.
     *
     * @param fd File descriptor of the virtual device
     * @param btn Button to release
     */
    void send_release_event(int fd, Button btn);
}