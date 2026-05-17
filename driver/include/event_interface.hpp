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
     * @brief Send relative mouse movement events.
     *
     * @param x Relative movement along X axis
     * @param y Relative movement along Y axis
     */
    virtual void send_move_event(int x, int y) = 0;

    /**
     * @brief Send scroll wheel events.
     *
     * @param val Scroll amount (positive = up, negative = down)
     */
    virtual void send_scroll_event(int val) = 0;

    /**
     * @brief Send a button press event.
     *
     * @param btn Button to press
     */
    virtual void send_press_event(Button btn) = 0;

    /**
     * @brief Send a button release event.
     *
     * @param btn Button to release
     */
    virtual void send_release_event(Button btn) = 0;
};