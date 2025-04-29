/**************************************************************************************************/
/**
 * \file   test-mackie-control.cc
 * \brief  Tests for Mackie Control Protocol classes
 */
/**************************************************************************************************/

#include <gtest/gtest.h>
#include "proto-mcu/mackie-msg.h"

using namespace mcu;

/**************************************************************************************************/

TEST(MidiMcuMsgTest, TestIsVpotRotation)
{
    // Success: V-Pot rotation on MIDI channel 0
    midi::midi_msg_t message_ok = {0xB0, 0x10, 0x01};
    MidiMcuMsg msg_ok(message_ok);
    EXPECT_TRUE(msg_ok.isVpotRotation());

    // Fail: V-Pot rotation on wrong MIDI channel
    midi::midi_msg_t message_fail = {0xB1, 0x10, 0x01};
    MidiMcuMsg msg_fail(message_fail);
    EXPECT_FALSE(msg_fail.isVpotRotation());
}

/**************************************************************************************************/

TEST(MidiMcuMsgTest, TestIsExternalControl)
{
    // Success: External control on MIDI channel 0
    midi::midi_msg_t message_ok = {0xB0, 0x2E, 0x01};
    MidiMcuMsg msg_ok(message_ok);
    EXPECT_TRUE(msg_ok.isExternalControl());

    // Fail: External control on wrong MIDI channel
    midi::midi_msg_t message_fail = {0xB2, 0x2E, 0x01};
    MidiMcuMsg msg_fail(message_fail);
    EXPECT_FALSE(msg_fail.isExternalControl());
}

/**************************************************************************************************/

TEST(MidiMcuMsgTest, TestIsJogWheel)
{
    // Success: Jog Wheel on MIDI channel 0
    midi::midi_msg_t message_ok = {0xB0, 0x3C, 0x01}; // Jog wheel is usually 0x3C
    MidiMcuMsg msg_ok(message_ok);
    EXPECT_TRUE(msg_ok.isJogWheel());

    // Fail: Jog Wheel on wrong MIDI channel
    midi::midi_msg_t message_fail = {0xB3, 0x3C, 0x01};
    MidiMcuMsg msg_fail(message_fail);
    EXPECT_FALSE(msg_fail.isJogWheel());
}

/**************************************************************************************************/

TEST(MidiMcuMsgTest, TestIsTimecodeDigit)
{
    // Success: Timecode on MIDI channel 0
    midi::midi_msg_t message_ok0 = {0xB0, 0x40, 0x01};
    MidiMcuMsg msg_ok0(message_ok0);
    EXPECT_TRUE(msg_ok0.isTimecodeDigit());

    // Success: Timecode on MIDI channel 15
    midi::midi_msg_t message_ok15 = {0xBF, 0x40, 0x01};
    MidiMcuMsg msg_ok15(message_ok15);
    EXPECT_TRUE(msg_ok15.isTimecodeDigit());

    // Fail: Timecode on wrong MIDI channel
    midi::midi_msg_t message_fail = {0xB2, 0x40, 0x01};
    MidiMcuMsg msg_fail(message_fail);
    EXPECT_FALSE(msg_fail.isTimecodeDigit());
}

/**************************************************************************************************/

TEST(MidiMcuMsgTest, TestIsAssignmentDigit)
{
    // Success: Assignment on MIDI channel 0
    midi::midi_msg_t message_ok0 = {0xB0, 0x4A, 0x01};
    MidiMcuMsg msg_ok0(message_ok0);
    EXPECT_TRUE(msg_ok0.isAssignmentDigit());

    // Success: Assignment on MIDI channel 15
    midi::midi_msg_t message_ok15 = {0xBF, 0x4A, 0x01};
    MidiMcuMsg msg_ok15(message_ok15);
    EXPECT_TRUE(msg_ok15.isAssignmentDigit());

    // Fail: Assignment on wrong MIDI channel
    midi::midi_msg_t message_fail = {0xB4, 0x4A, 0x01};
    MidiMcuMsg msg_fail(message_fail);
    EXPECT_FALSE(msg_fail.isAssignmentDigit());
}

/**************************************************************************************************/