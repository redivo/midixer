#include "MIDIUSB.h"
#include "messages.h"





void setup() {
  Serial.begin(115200);
}

void loop() {
    midiEventPacket_t rx;

    do {
        rx = MidiUSB.read();
        if (rx.header != 0) {
            MidiMCU event(rx);
            Serial.print(event.getString());
        }


        //MidiUSB.flush();
        //Serial.print("Send start\r\n");
        //MidiUSB.sendMIDI(MidiEvtStartFromBeginning().raw_data);
        //delay(5000);
        //Serial.print("Send stop\r\n");
        //MidiUSB.sendMIDI(MidiEvtStop().raw_data);
        //delay(5000);

    } while (rx.header != 0);
}


/*





























Message Type         MS Nybble  LS Nybble              # of Data Bytes  Data Byte 1         Data Byte 2
Note Of              0x8        Channel                2                Note Number         Velocity
Note On              0x9        Channel                2                Note Number         Velocity
Polyphonic Pressure  0xA        Channel                2                Note Number         Pressure
Control Change       0xB        Channel                2                Controller Number   Value
Program Change       0xC        Channel                1                Program Number      -none-
Channel Pressure     0xD        Channel                1                Pressure            -none-
Pitch Bend           0xE        Channel                2                Bend LSB (7-bits)   Bend MSB (7-bits)
System               0xF        further specification  variable         variable            variable








==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x32
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x33
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x64
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x65
Byte 3: 0x00

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x4b
Byte 3: 0x30

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x4a
Byte 3: 0x31

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x12

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x00
Byte 2: 0x52
Byte 3: 0x45

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x41
Byte 2: 0x50
Byte 3: 0x45

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x52
Byte 2: 0x21
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x49
Byte 2: 0x6e
Byte 3: 0x69

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x74
Byte 2: 0x69
Byte 3: 0x61

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x6c
Byte 2: 0x69
Byte 3: 0x7a

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x69
Byte 2: 0x6e
Byte 3: 0x67

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x2e
Byte 2: 0x2e
Byte 3: 0x2e

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x50
Byte 3: 0x6c

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x65
Byte 2: 0x61
Byte 3: 0x73

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x65
Byte 2: 0x20
Byte 3: 0x77

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x61
Byte 2: 0x69
Byte 3: 0x74

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x2e
Byte 2: 0x2e
Byte 3: 0x2e

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x00
Byte 2: 0x03
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x01
Byte 2: 0x03
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x02
Byte 2: 0x03
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x03
Byte 2: 0x03
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x04
Byte 2: 0x03
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x05
Byte 2: 0x03
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x06
Byte 2: 0x03
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x07
Byte 2: 0x03
Byte 3: 0xf7

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x0f
Byte 3: 0x00

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x1f
Byte 3: 0x00

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x2f
Byte 3: 0x00

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x3f
Byte 3: 0x00

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x4f
Byte 3: 0x00

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x5f
Byte 3: 0x00

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x6f
Byte 3: 0x00

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x7f
Byte 3: 0x00

==============================
PITCH_BEND
Header: 0x0e
Byte 1: 0xe0
Byte 2: 0x29
Byte 3: 0x00

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x30
Byte 3: 0x06

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x10
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x18
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x08
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x00
Byte 3: 0x00

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x12

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x00
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x00
Byte 2: 0x03
Byte 3: 0xf7

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x0f
Byte 3: 0x00

==============================
PITCH_BEND
Header: 0x0e
Byte 1: 0xe1
Byte 2: 0x29
Byte 3: 0x00

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x31
Byte 3: 0x06

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x11
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x19
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x09
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x01
Byte 3: 0x00

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x12

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x07
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x01
Byte 2: 0x03
Byte 3: 0xf7

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x1f
Byte 3: 0x00

==============================
PITCH_BEND
Header: 0x0e
Byte 1: 0xe2
Byte 2: 0x29
Byte 3: 0x00

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x32
Byte 3: 0x06

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x12
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x1a
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x0a
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x02
Byte 3: 0x00

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x12

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x0e
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x02
Byte 2: 0x03
Byte 3: 0xf7

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x2f
Byte 3: 0x00

==============================
PITCH_BEND
Header: 0x0e
Byte 1: 0xe3
Byte 2: 0x29
Byte 3: 0x00

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x33
Byte 3: 0x06

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x13
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x1b
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x0b
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x03
Byte 3: 0x00

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x12

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x15
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x03
Byte 2: 0x03
Byte 3: 0xf7

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x3f
Byte 3: 0x00

==============================
PITCH_BEND
Header: 0x0e
Byte 1: 0xe4
Byte 2: 0x29
Byte 3: 0x00

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x34
Byte 3: 0x06

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x14
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x1c
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x0c
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x04
Byte 3: 0x00

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x12

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x1c
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x04
Byte 2: 0x03
Byte 3: 0xf7

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x4f
Byte 3: 0x00

==============================
PITCH_BEND
Header: 0x0e
Byte 1: 0xe5
Byte 2: 0x29
Byte 3: 0x00

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x35
Byte 3: 0x06

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x15
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x1d
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x0d
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x05
Byte 3: 0x00

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x12

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x23
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x05
Byte 2: 0x03
Byte 3: 0xf7

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x5f
Byte 3: 0x00

==============================
PITCH_BEND
Header: 0x0e
Byte 1: 0xe6
Byte 2: 0x29
Byte 3: 0x00

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x36
Byte 3: 0x06

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x16
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x1e
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x0e
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x06
Byte 3: 0x00

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x12

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x2a
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x06
Byte 2: 0x03
Byte 3: 0xf7

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x6f
Byte 3: 0x00

==============================
PITCH_BEND
Header: 0x0e
Byte 1: 0xe7
Byte 2: 0x29
Byte 3: 0x00

==============================
CONTROL_CHANGE
Header: 0x0b
Byte 1: 0xb0
Byte 2: 0x37
Byte 3: 0x06

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x17
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x1f
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x0f
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x07
Byte 3: 0x00

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x12

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x31
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x20
Byte 2: 0x20
Byte 3: 0xf7

==============================
SYSTEM
Header: 0x04
Byte 1: 0xf0
Byte 2: 0x00
Byte 3: 0x00

==============================
UNKNOWN: 4
Header: 0x04
Byte 1: 0x66
Byte 2: 0x14
Byte 3: 0x20

==============================
UNKNOWN: 7
Header: 0x07
Byte 1: 0x07
Byte 2: 0x03
Byte 3: 0xf7

==============================
CHANNEL_PRESSURE
Header: 0x0d
Byte 1: 0xd0
Byte 2: 0x7f
Byte 3: 0x00

==============================
PITCH_BEND
Header: 0x0e
Byte 1: 0xe8
Byte 2: 0x52
Byte 3: 0x5b

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x4a
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x4b
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x4c
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09                                         
Byte 1: 0x90                                         
Byte 2: 0x4d                                         
Byte 3: 0x00                                         

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x4e
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x73
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x5a
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x71
Byte 3: 0x00

==============================
NOTE_ON
Header: 0x09
Byte 1: 0x90
Byte 2: 0x72
Byte 3: 0x7f






*/
