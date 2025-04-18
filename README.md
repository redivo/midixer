# MIdiXER

MIdiXER is a MIDI control project for DAWs.

- Install `arduino-cli`: https://docs.arduino.cc/arduino-cli/
avr-g++
sudo apt install gcc-avr binutils-avr avr-libc

avr-g++ -c \
  -mmcu=atmega32u4 \
  -DF_CPU=16000000UL \
  -Os -std=c++17 \
  -I../software/include/ \
  -o ./midi-msg.o \
  ../software/src/midi-msg.cc
avr-ar rcs libmidixer.a midixer.o
