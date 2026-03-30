# Virtual Mouse (uinput)

A minimal C++ project that creates and controls a virtual mouse using the Linux **uinput** subsystem.

## Project Structure

```
├── CMakeLists.txt
├── include
├── README.md
├── scripts
│   ├── build.sh             # Build project
│   ├── clean.sh             # Clean build files
│   └── run.sh               # Run executable
└── src 
```

## Requirements

* Linux (with `/dev/uinput`)
* C++ compiler (g++)
* CMake

## Build

```bash
chmod +x ./scripts/build.sh
./scripts/build.sh
```
or

`bash -c ./scripts/build.sh`

## Run

```bash
chmod +x ./scripts/run.sh
./scripts/run.sh
```

Or:

`bash -c ./scripts/run.sh`

\*requires *sudo* priviliges

## How it works

The C++ code uses the **uinput** interface provided by the system to emulate a virtual mouse and controll features like cursor movement and button clicks

## Features

* Relative mouse movement
* Mouse button press/release
* Scroll support
* Adjustable sensitivity

## Notes

* Requires root or proper udev permissions
* Works on both X11 and Wayland
* No external libraries required
