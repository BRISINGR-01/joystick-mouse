#include <uinput_interface.hpp>
#include <constants.hpp>

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
    /// File descriptor for `/dev/uinput` (virtual device handle)
    int fd;

    /// Movement multiplier (higher = faster cursor)
    int sensitivity = 2;

public:
    /**
     * @brief Construct and initialize the virtual mouse device.
     *
     * Opens `/dev/uinput`, configures capabilities (REL_X, REL_Y, buttons, etc.), and creates the device.
     */
    Mouse();

    /**
     * @brief Destroy the virtual mouse device.
     *
     * Destroys the uinput device and closes the file descriptor.
     */
    ~Mouse();

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