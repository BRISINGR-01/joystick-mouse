cmake_minimum_required(VERSION 3.20)

project(JoystickMouse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Source files
file(GLOB SRC CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../include)

if(TEST_SRC)
    file(GLOB TEST_SRC CONFIGURE_DEPENDS "test/*.cpp")

    add_executable(${PROJECT_NAME}-test ${TEST_SRC})

    target_include_directories(${PROJECT_NAME}-test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${GENERATED_DIR}
    )


    add_test(NAME ${PROJECT_NAME}-test
        COMMAND ${PROJECT_NAME}-test
    )
endif()