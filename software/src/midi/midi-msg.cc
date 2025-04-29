/**************************************************************************************************/
/**
 * \file   midi-msg.cc
 * \brief  Implementation of generic MIDI messages
 *
 * This file was written based on information of these two references:
 *   https://learn.sparkfun.com/tutorials/midi-tutorial/
 *   https://midi.org/summary-of-midi-1-0-messages
 */
/**************************************************************************************************/

#include "midi/midi-msg.h"

#include <stdio.h>
#include <string.h>

namespace midi {

/**************************************************************************************************/

MidiMsg::MidiMsg(midi_msg_t event) : raw_data_(event)
{
}

/**************************************************************************************************/

midi_msg_type_t MidiMsg::getMsgType()
{
    uint8_t type = getRawMsgType();

    // Search in codes
    switch (type) {
        case MSG_TYPE_NONE:
        case MSG_TYPE_NOTE_OFF:
        case MSG_TYPE_NOTE_ON:
        case MSG_TYPE_POLYPHONIC_PRESSURE:
        case MSG_TYPE_CONTROL_CHANGE:
        case MSG_TYPE_PROGRAM_CHANGE:
        case MSG_TYPE_CHANNEL_PRESSURE:
        case MSG_TYPE_PITCH_BEND:
        case MSG_TYPE_SYSTEM:
            return static_cast<midi_msg_type_t>(type);

        default:
            return MSG_TYPE_UNKNOWN;
    }
}

/**************************************************************************************************/

int8_t MidiMsg::getControl()
{
    if (getMsgType() != MSG_TYPE_CONTROL_CHANGE) {
        return -1;
    }

    // Note is the 7 LSB of byte 2
    return raw_data_.byte2 & 0x7F;
}


/**************************************************************************************************/

const char* MidiMsg::getString()
{
    const char* type = getMsgTypeStr();
    const char* raw_data = getRawDataString();
    static char buff[MIDI_MSG_MAX_STRING_SIZE];

    sprintf(buff, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", type, raw_data);

    return buff;
}

/**************************************************************************************************/

const char* MidiMsg::getMsgTypeStr()
{
    // Define locally a structure for a maping
    typedef struct {
        midi_msg_type_t type;
        const char* name;
    } midi_type_to_name_map_t;

    // Fill the map
    const midi_type_to_name_map_t midi_type_to_string[] = {
            { MSG_TYPE_UNKNOWN, "UNKNOWN" },
            { MSG_TYPE_NONE, "NONE (empty message)" },
            { MSG_TYPE_NOTE_OFF, "NOTE OFF" },
            { MSG_TYPE_NOTE_ON, "NOTE ON" },
            { MSG_TYPE_POLYPHONIC_PRESSURE, "POLYPHONIC PRESSURE" },
            { MSG_TYPE_CONTROL_CHANGE, "CONTROL CHANGE" },
            { MSG_TYPE_PROGRAM_CHANGE, "PROGRAM CHANGE" },
            { MSG_TYPE_CHANNEL_PRESSURE, "CHANNEL PRESSURE" },
            { MSG_TYPE_PITCH_BEND, "PITCH BEND" },
            { MSG_TYPE_SYSTEM, "SYSTEM" }
    };

    // Find for type name
    auto type = getMsgType();
    for (const auto& entry : midi_type_to_string) {
        if (entry.type == type) {
            return entry.name;
        }
    }

    return "UNKNOWN";
}

/**************************************************************************************************/

const char* MidiMsg::getRawDataString()
{
    static char buff[MIDI_MSG_MAX_RAW_DATA_STRING_SIZE] = "";

    sprintf(buff, "Byte 1: 0x%02x\r\n"
                  "Byte 2: 0x%02x\r\n"
                  "Byte 3: 0x%02x\r\n", raw_data_.byte1,
                                        raw_data_.byte2,
                                        raw_data_.byte3);

    return buff;
}

/**************************************************************************************************/

uint8_t MidiMsg::getRawMsgType()
{
    // MIDI Message type is in MS nybble of byte 1
    return (raw_data_.byte1 & 0xF0) >> 4;
}

/**************************************************************************************************/

uint8_t MidiMsg::getRawMidiChannel()
{
    // MIDI Channel is inLS nybble of byte 1
    return (raw_data_.byte1 & 0x0F);
}

/**************************************************************************************************/

uint8_t MidiMsg::getRawNote()
{
    // Note is the 7 LSB of byte 2
    return raw_data_.byte2 & 0x7F;
}

/**************************************************************************************************/

uint8_t MidiMsg::getRawVelocity()
{
    // Note is the 7 LSB of byte 3
    return raw_data_.byte3 & 0x7F;
}

/**************************************************************************************************/

uint16_t MidiMsg::getRawPitchBend()
{
    // Byte 2 has the 7 LS bits
    uint8_t lsb = (raw_data_.byte2 & 0x7F);

    // Byte 3 has the 7 MS bits
    uint8_t msb = (raw_data_.byte3 & 0x7F);

    return (msb << 7) + lsb;
}

/**************************************************************************************************/

midi_msg_t MidiMsg::getRawData()
{
    return raw_data_;
}

/**************************************************************************************************/

}  // namespace midi
