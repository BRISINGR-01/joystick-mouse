cmake_minimum_required(VERSION 3.20)

project(JoystickMouse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Protobuf REQUIRED)
find_package(Protobuf REQUIRED)
find_package(absl REQUIRED)

enable_testing()

# External generated protobuf directory
set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../generated)

file(GLOB PROTO_SRC CONFIGURE_DEPENDS "${GENERATED_DIR}/*.cc")

# Source files
file(GLOB SRC CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME}
    ${SRC}
    ${PROTO_SRC}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Protobuf_LIBRARIES}
    absl::base
    absl::strings
    absl::log
    absl::log_internal_check_op
    absl::raw_logging_internal
    absl::synchronization
    absl::time
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GENERATED_DIR}
)


if(TEST_SRC)
    file(GLOB TEST_SRC CONFIGURE_DEPENDS "test/*.cpp")

    add_executable(${PROJECT_NAME}-test
        ${TEST_SRC}
        ${PROTO_SRC}
    )

    target_include_directories(${PROJECT_NAME}-test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${GENERATED_DIR}
    )


    add_test(NAME ${PROJECT_NAME}-test
        COMMAND ${PROJECT_NAME}-test
    )
endif()