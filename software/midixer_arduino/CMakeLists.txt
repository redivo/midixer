add_custom_target(
    build ALL
    COMMAND ${CMAKE_SOURCE_DIR}/midixer_arduino/compile.sh
                ${BOARD_NAME_FQBN} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}
    COMMENT "Compiling Arduino top file..."
    DEPENDS midixer
    VERBATIM
)
add_dependencies(build midixer)

string(CONFIGURE [[
    message(STATUS "📦 Installation: upload to Arduino!")
    message(STATUS "📦 Using FQBN: ${BOARD_NAME_FQBN}")
    message(STATUS "📦 Using SRC_DIR: ${CMAKE_SOURCE_DIR}")
    message(STATUS "📦 Using BIN_DIR: ${CMAKE_BINARY_DIR}")
    message(STATUS "📦 Using port SERIAL_PORT: ${SERIAL_PORT}")

    SET(SERIAL_PORT ${SERIAL_PORT})
    if(NOT SERIAL_PORT)
        message(FATAL_ERROR "❌ SERIAL_PORT is not set or empty. "
                            "Please use './build-arduino-micro.sh /dev/tty???'")
    endif()
    execute_process(COMMAND ${CMAKE_SOURCE_DIR}/midixer_arduino/compile.sh
                ${BOARD_NAME_FQBN} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${SERIAL_PORT})
]] INSTALL_COMMAND)
install(CODE "${INSTALL_COMMAND}")
