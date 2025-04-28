/**************************************************************************************************/
/**
 * \file   midixer_arduino.ino
 * \brief  Top level of MIdiXER. Arduino implementation
 */
/**************************************************************************************************/

#include "MIDIUSB.h"
#include "midi-msg.h"
#include "track.h"
#include "mackie-control.h"

void setup()
{
  Serial.begin(115200);
}

void loop() {
    midiEventPacket_t rx;
    midixer::Track track;

    do {
        rx = MidiUSB.read();
        if (rx.header != 0) {


            midi::midi_msg_t midi = {
                .byte1 = rx.byte1,
                .byte2 = rx.byte2,
                .byte3 = rx.byte3,
            };

            mcu::MidiMcuMsg mcu(midi);
            Serial.print(mcu.getString());
        }

    } while (rx.header != 0);
}
