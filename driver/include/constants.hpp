#define DEVICE_NAME "Joystick Mouse"
#define VENDOR_ID 0x1234
#define PRODUCT_ID 0x5678

#ifndef constants_h
#define constants_h

enum Button
{
    Left,
    Right,
    Forth,
    Back,
    Middle
};

enum Action
{
    Move,
    Scroll,
    Press,
    Release
};

#endif