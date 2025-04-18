cmake_minimum_required(VERSION 3.22)
project(MIdiXER)

# Includes
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# Configure environment according to target
if(${TARGET} STREQUAL "arduino_micro")
    message(STATUS "🤖 Compiling for Arduino Micro")

    # Set parameters
    set(MCU atmega32u4)
    set(F_CPU 16000000UL)
    set(BOARD_NAME_FQBN arduino:avr:micro)
    set(CMAKE_C_COMPILER avr-gcc)
    set(CMAKE_CXX_COMPILER avr-g++)
    set(CMAKE_AR avr-ar)

    # Set compilation flags
    set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -std=c++17")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

    # Add arduino compilation
    add_subdirectory(midixer_arduino)
else()
    message(STATUS "💻 Compiling for testing")

    # Set compilation flags
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

    # Add tests compilation
    add_subdirectory(tests)
endif()

# Subdirectories
add_subdirectory(src)
