cmake_minimum_required(VERSION 3.20)

project(JoystickMouse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files (excluding main which has Arduino dependency)
file(GLOB SRC_LIB CONFIGURE_DEPENDS "src/*.cpp")
list(REMOVE_ITEM SRC_LIB "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${SRC_LIB})

target_include_directories(${PROJECT_NAME}_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

# Testing
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()

    find_package(GTest REQUIRED)

    file(GLOB TEST_SRC CONFIGURE_DEPENDS "test/*.cpp")

    add_executable(${PROJECT_NAME}-test ${TEST_SRC})

    target_include_directories(${PROJECT_NAME}-test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    )

    target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME}_lib GTest::GTest GTest::Main pthread)

    add_test(NAME ${PROJECT_NAME}-test
        COMMAND ${PROJECT_NAME}-test
    )
endif()