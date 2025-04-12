add_custom_target(
    build ALL
    COMMAND ${CMAKE_SOURCE_DIR}/midixer_arduino/compile.sh
                ${BOARD_NAME_FQBN} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}
    COMMENT "Compiling Arduino top file..."
    DEPENDS midixer
    VERBATIM
)
add_dependencies(build midixer)

message(STATUS ${CMAKE_SOURCE_DIR})
string(CONFIGURE [[
    message(STATUS "📦 Installation: upload to Arduino!")
    message(STATUS "📦 Using port defined in env var ARDUINO_PORT: $ENV{ARDUINO_PORT}")

    if(NOT DEFINED ENV{ARDUINO_PORT})
        message(FATAL_ERROR "❌ Env var ARDUINO_PORT is not set. "
                            "Please use 'ARDUINO_PORT=/tty/??? make install'")
    endif()
    execute_process(COMMAND ${CMAKE_SOURCE_DIR}/midixer_arduino/compile.sh
                ${BOARD_NAME_FQBN} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} $ENV{ARDUINO_PORT})
]] INSTALL_COMMAND)
install(CODE "${INSTALL_COMMAND}")
