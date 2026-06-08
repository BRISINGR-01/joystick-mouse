ROOT_DIR := $(realpath .)
BUILD_DIR := $(ROOT_DIR)/build
UDEV_RULES := /etc/udev/rules.d/80-joystickmouse.rules

.PHONY: help build clean install uninstall run test

help:
	@echo "Usage: make <target>"
	@echo ""
	@echo "Available targets:"
	@echo "  build     Configure and build the project with CMake"
	@echo "  clean     Remove the build directory"
	@echo "  install   Build, install binary and udev rule"
	@echo "  uninstall Remove udev rules and joystick-mouse binary"
	@echo "  run       Run the built binary (requires sudo)"
	@echo "  test      Build and run tests with CTest"
	@echo "  help      Show this help message"

build:
	cmake -S $(ROOT_DIR) -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

install: build
	sudo mv $(BUILD_DIR)/JoystickMouse /bin/joystick-mouse
	sudo cp $(ROOT_DIR)/udev/80-joystickmouse.rules $(UDEV_RULES)
	sudo udevadm control --reload
	@echo -n "udev rule status: "; test -f $(UDEV_RULES) && echo "loaded" || echo "MISSING"

uninstall:
	sudo rm $(UDEV_RULES)
	sudo udevadm control --reload
	@echo -n "udev rule status: "; test ! -f $(UDEV_RULES) && echo "removed" || echo "STILL PRESENT"
	sudo rm /bin/joystick-mouse

run: build
	sudo $(BUILD_DIR)/JoystickMouse

test:
	cmake -S $(ROOT_DIR) -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
	ctest --test-dir $(BUILD_DIR)
