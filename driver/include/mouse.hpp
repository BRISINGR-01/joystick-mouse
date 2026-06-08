#pragma once
#include <event_interface.hpp>
#include <constants.hpp>

#include <memory>

#define SENSITIVITY 15
#define MOVEMENT_STEP_PART 5
#define MOVEMENT_STEP_DELAY 100

/**
 * @class Mouse
 * @brief Virtual mouse interface using uinput.
 *
 * Provides a high-level API to control a virtual mouse device:
 * movement, scrolling, and button actions.
 */
class Mouse
{
private:
    std::unique_ptr<EventInterface> event_interface;

    /// Movement multiplier (higher = faster cursor)
    float sensitivity;

public:
    /// Construct and initialize the virtual mouse device.
    Mouse(std::unique_ptr<EventInterface> event_interface);

    /**
     * @brief Set mouse sensitivity.
     * @param val Multiplier applied to movement deltas (higher -> faster).
     */
    void set_sensitivity(int val);

    /**
     * @brief Move the mouse cursor.
     * @param x Relative movement on X axis
     * @param y Relative movement on Y axis
     * Movement is scaled by sensitivity.
     */
    void move(int x, int y);

    /**
     * @brief Scroll vertically.
     * @param val Scroll amount (positive = up, negative = down)
     */
    void scroll(int val);

    /**
     * @brief Press a mouse button.
     * @param btn Button to press (LEFT, RIGHT, MIDDLE, BACK and FORWARD)
     */
    void press(Button btn);

    /**
     * @brief Release a mouse button.
     * @param btn Button to release
     */
    void release(Button btn);
};