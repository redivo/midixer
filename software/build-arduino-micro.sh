#!/bin/bash

# Create build directory and enter in it
mkdir -p _build_arduino_micro
cd _build_arduino_micro

# Create cmake environment
cmake -DTARGET=arduino_micro ..

# Compile
make
