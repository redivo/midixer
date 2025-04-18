#!/bin/bash

# This file is a complement of CMakeLists.txt. For some reason this command line does not work well
# when executed by CMake.
# The option --build-property compiler.libraries.ldflags="-L$3/src -lmidixer" is not correctly
# passed to compiler and the loader fails.
# To workaround this the CMakeList.txt call this script
#
#   First argument is BOARD_NAME_FQBN
#   Second argument is CMAKE_SOURCE_DIR
#   Third argument is CMAKE_BINARY_DIR
#   (optional) Fourth argument is the serial port to upload the program

# Fill upload arg to be set in compilation line. If 4th argument is passed, assume it is the serial
# port and it is an upload execution
UPLOAD_ARG=""
if [ -n "$4" ]; then
    UPLOAD_ARG="-p $4 -u"
fi

arduino-cli compile \
    -b $1 \
    $UPLOAD_ARG \
    --build-property compiler.cpp.extra_flags="-I$2/include" \
    --build-property compiler.libraries.include.path="$2/include" \
    --build-property compiler.libraries.ldflags="-L$3/src -lmidixer" \
    $2/midixer_arduino
