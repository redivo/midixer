#!/bin/bash

# Create build directory and enter in it
mkdir -p _build_arduino_micro
cd _build_arduino_micro

echo $1

# Fill installation args if first parameter was passed
SERIAL_PORT_LINE=""
INSTALLATION_LINE=""
if [ -n "$1" ]; then
    SERIAL_PORT_LINE="-DSERIAL_PORT=$1"
    INSTALLATION_LINE="make install"
fi

# Create cmake environment
cmake -DTARGET=arduino_micro $SERIAL_PORT_LINE ..

# Compile
make

# Install
$INSTALLATION_LINE