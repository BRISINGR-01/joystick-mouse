cmake_minimum_required(VERSION 3.20)

project(JoystickMouse)

file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
include_directories("${PROJECT_SOURCE_DIR}/include")
