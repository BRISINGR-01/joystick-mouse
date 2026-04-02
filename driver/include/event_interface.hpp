#pragma once
#include <constants.hpp>

#include <iostream>

/**
 * @class EventInterface
 * @brief Defines an interface to generating kernel mouse related events
 *
 * Provides a high-level API to control a virtual mouse device:
 * movement, scrolling, and button actions.
 */
class EventInterface
{
public:
    EventInterface() = default;          // All constructors are to prevent
    virtual ~EventInterface() = default; // multiple copies of EventInterface classes

public:
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
    virtual int create_device(std::string device_name, unsigned short vendor_id, unsigned short product_id) = 0;

    /**
     * @brief Destroy a virtual uinput device.
     * @param fd File descriptor of the device to destroy
     */
    virtual void destroy_device(int fd) = 0;

    /**
     * @brief Send relative mouse movement events.
     *
     * @param fd File descriptor of the virtual device
     * @param x Relative movement along X axis
     * @param y Relative movement along Y axis
     */
    virtual void send_move_event(int fd, int x, int y) = 0;

    /**
     * @brief Send scroll wheel events.
     *
     * @param fd File descriptor of the virtual device
     * @param val Scroll amount (positive = up, negative = down)
     */
    virtual void send_scroll_event(int fd, int val) = 0;

    /**
     * @brief Send a button press event.
     *
     * @param fd File descriptor of the virtual device
     * @param btn Button to press
     */
    virtual void send_press_event(int fd, Button btn) = 0;

    /**
     * @brief Send a button release event.
     *
     * @param fd File descriptor of the virtual device
     * @param btn Button to release
     */
    virtual void send_release_event(int fd, Button btn) = 0;
};