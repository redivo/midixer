/**************************************************************************************************/
/**
 * \file   midixer_arduino.ino
 * \brief  Top level of MIdiXER. Arduino implementation
 */
/**************************************************************************************************/

#include "MIDIUSB.h"
#include "midi-msg.h"

void setup()
{
  Serial.begin(115200);
}

void loop() {
    midiEventPacket_t rx;

    do {
        rx = MidiUSB.read();
        if (rx.header != 0) {


            midi::midi_msg_t midi = {
                .byte1 = rx.byte1,
                .byte2 = rx.byte2,
                .byte3 = rx.byte3,
            };

            midi::MidiMsg event(midi);
            Serial.print(event.getString());
        }

    } while (rx.header != 0);
}
