/**************************************************************************************************/
/**
 * \file   test-midi-msg.cc
 * \brief  Tests for MidiMsg class
 */
/**************************************************************************************************/

#include <gtest/gtest.h>
#include "midi/midi-msg.h"

using namespace midi;

/**************************************************************************************************/

TEST(MidiMsgTest, DefaultConstructorDoesNotCrash)
{
    MidiMsg *msg = new MidiMsg();
    delete msg;
}

/**************************************************************************************************/

TEST(MidiMsgTest, ConstructorStoresRawData)
{
    midi_msg_t midi = {
        .byte1 = 0xB0,
        .byte2 = 0x87,
        .byte3 = 0x64,
    };
    MidiMsg msg(midi);

    EXPECT_EQ(msg.getRawMsgType(), 0xB);
    EXPECT_EQ(msg.getRawMidiChannel(), 0);
    EXPECT_EQ(msg.getRawNote(), 0x07);  // MSb removed
    EXPECT_EQ(msg.getRawVelocity(), 0x64);
}

/**************************************************************************************************/

TEST(MidiMsgTest, GetControlOk)
{
    midi_msg_t midi = {
        .byte1 = 0xB0,
        .byte2 = 0x87,
        .byte3 = 0x64,
    };
    MidiMsg msg(midi);

    EXPECT_EQ(msg.getControl(), 0x07);  // MSb removed
}

/**************************************************************************************************/

TEST(MidiMsgTest, GetControlError)
{
    midi_msg_t midi = {
        .byte1 = 0xC0, // NOT control change
        .byte2 = 0x87,
        .byte3 = 0x64,
    };
    MidiMsg msg(midi);

    EXPECT_EQ(msg.getControl(), -1);
}

/**************************************************************************************************/

TEST(MidiMsgTest, getMsgTypeOk)
{
    midi_msg_t midi = {
        .byte1 = 0xD1,
        .byte2 = 0x87,
        .byte3 = 0x64,
    };
    MidiMsg msg(midi);

    EXPECT_EQ(msg.getMsgType(), MSG_TYPE_CHANNEL_PRESSURE);
}

/**************************************************************************************************/

TEST(MidiMsgTest, getMsgTypelError)
{
    midi_msg_t midi = {
        .byte1 = 0x20, // NOT a know type
        .byte2 = 0x87,
        .byte3 = 0x64,
    };
    MidiMsg msg(midi);

    EXPECT_EQ(msg.getMsgType(), MSG_TYPE_UNKNOWN);
}

/**************************************************************************************************/

TEST(MidiMsgTest, getMsgTypelNone)
{
    midi_msg_t midi = {
        .byte1 = 0x00, // ZEROED
        .byte2 = 0x87,
        .byte3 = 0x64,
    };
    MidiMsg msg(midi);

    EXPECT_EQ(msg.getMsgType(), MSG_TYPE_NONE);
}

/**************************************************************************************************/

TEST(MidiMsgTest, GetMsgTypeReturnsControlChange)
{
    midi_msg_t midi = {
        .byte1 = 0xE0,
        .byte2 = 0x87,
        .byte3 = 0x64,
    };
    MidiMsg msg(midi);

    EXPECT_EQ(msg.getMsgType(), MSG_TYPE_PITCH_BEND);
}

/**************************************************************************************************/

TEST(MidiMsgTest, GetStringReturnsNonNull)
{
    midi_msg_t midi = {
        .byte1 = 0x90,
        .byte2 = 0x45,
        .byte3 = 0x7F,
    };  // NOTE_ON message
    MidiMsg msg(midi);

    ASSERT_NE(msg.getString(), nullptr);
    EXPECT_STREQ(msg.getString(), "==============================\r\n"
                                  "NOTE ON\r\n"
                                  "Byte 1: 0x90\r\n"
                                  "Byte 2: 0x45\r\n"
                                  "Byte 3: 0x7f\r\n\r\n");
}

/**************************************************************************************************/

TEST(MidiMsgTest, GetRawData)
{
    midi_msg_t midi = {
        .byte1 = 0x90,
        .byte2 = 0x45,
        .byte3 = 0x7F,
    };
    MidiMsg msg(midi);

    ASSERT_EQ(midi, msg.getRawData());
}

/**************************************************************************************************/

TEST(MidiMsgTest, GetRawPitchBend)
{
    midi_msg_t midi = {
        .byte1 = 0xE0,
        .byte2 = 0x87, // lsb
        .byte3 = 0x64, // msb
    };
    MidiMsg msg(midi);

    /*
     *         msb      lsb
     *     +-------------------
     * hex |   0x64      0x87
     * bit | 01100100  10000111  ---only 7 lsb are considered---+
     *     |                                                    |
     * bit |  1100100   0000111  <------------------------------+
     * bit |     11001000000111  Concatenated
     * hex |             0x3207
     * dec |             12807
     */
    ASSERT_EQ(12807, msg.getRawPitchBend());
}

/**************************************************************************************************/
