#!/bin/bash

# Create build directory and enter in it
mkdir -p _build_tests
cd _build_tests

# Create cmake environment
cmake -DTARGET=tests ..

# Compile
make
