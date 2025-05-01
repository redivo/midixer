/**************************************************************************************************/
/**
 * \file   midixer_arduino.ino
 * \brief  Top level of MIdiXER. Arduino implementation
 */
/**************************************************************************************************/

#include "MIDIUSB.h"
#include "proto-mcu/mackie-msg.h"
#include "proto-mcu/mackie-protocol.h"

class MidixerDebug : public midixer::MidixerCbs {
   public:
    void updateTrackName(uint8_t track_num, const char *track_name)
    {
        String s("===>> Track " + String(track_num) + " name: " + String(track_name) + "\r\n");
        Serial.print(s);
    }

    void updateRecArm(uint8_t track_num, bool arm)
    {
        String s("===>> Track " + String(track_num) + " REC: " + String(arm) + "\r\n");
        Serial.print(s);
    }

    void updateSolo(uint8_t track_num, bool solo)
    {
        String s("===>> Track " + String(track_num) + " Solo: " + String(solo) + "\r\n");
        Serial.print(s);
    }

    void updateMute(uint8_t track_num, bool mute)
    {
        String s("===>> Track " + String(track_num) + " Mute: " + String(mute) + "\r\n");
        Serial.print(s);
    }

    void updateFaderPosition(uint8_t track_num, uint16_t pos)
    {
        String s("===>> Track " + String(track_num) + " Fader: " + String(pos) + "\r\n");
        Serial.print(s);
    }

};

void setup()
{
  Serial.begin(115200);
}

void loop() {
    MidixerDebug debug;
    mcu::MackieProtocol proto(&debug);
    midiEventPacket_t rx;

    do {
        rx = MidiUSB.read();
        if (rx.header != 0) {


          midi::midi_msg_t midi = {
              .byte1 = rx.byte1,
              .byte2 = rx.byte2,
              .byte3 = rx.byte3,
          };

          mcu::MidiMcuMsg mcu(midi);
          proto.handleMessage(mcu);
      }

    } while (rx.header != 0);
}
