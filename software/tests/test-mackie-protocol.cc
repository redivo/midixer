/**************************************************************************************************/
/**
 * \file   test-mackie-protocol.cc
 * \brief  Tests for Mackie Control Protocol
 */
/**************************************************************************************************/

#include <gtest/gtest.h>
#include "midixer/midixer-cb-intf-mock.h"
#include "proto-mcu/mackie-protocol.h"

using namespace mcu;
using ::testing::_;
using ::testing::StrEq;

/**************************************************************************************************/

TEST(MackieProtocol, Constructor)
{
    midixer::MockMidixerCbs mock_midixer;
    MackieProtocol mackie_proto(&mock_midixer);
}

/**************************************************************************************************/

TEST(MackieProtocol, UnknownMessage)
{
    midixer::MockMidixerCbs mock_midixer;
    MackieProtocol mackie_proto(&mock_midixer);

    // Declare nothing will be called
    EXPECT_CALL(mock_midixer, updateTrackName(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateRecArm(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateSolo(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateMute(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateFaderPosition(_, _)).Times(0);

    // Create dummy message
    MidiMcuMsg msg({0, 0, 0});

    // Call handling
    mackie_proto.handleMessage(msg);
}

/**************************************************************************************************/

TEST(MackieProtocol, TrackName)
{
    midixer::MockMidixerCbs mock_midixer;
    MackieProtocol mackie_proto(&mock_midixer);

    // Declare expectations
    EXPECT_CALL(mock_midixer, updateTrackName(3, StrEq("Vocals "))).Times(1);
    EXPECT_CALL(mock_midixer, updateRecArm(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateSolo(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateMute(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateFaderPosition(_, _)).Times(0);

    // Create messages
    MidiMcuMsg msg_header1({0xF0, 0x00, 0x00}); // System message
    MidiMcuMsg msg_header2({0x66, 0x14, 0x12}); // Mackie Design (0x66), Mackie Control (0x14),
                                                // Update LCD (0x12)
    MidiMcuMsg msg_name_1({0x0E, 'V', 'o'}); // Track 3 ((3 - 1) * 7 = 14 = 0x0E)
    MidiMcuMsg msg_name_2({'c', 'a', 'l'});
    MidiMcuMsg msg_name_3({'s', ' ', 0x0F7});

    // Call handling
    mackie_proto.handleMessage(msg_header1);
    mackie_proto.handleMessage(msg_header2);
    mackie_proto.handleMessage(msg_name_1);
    mackie_proto.handleMessage(msg_name_2);
    mackie_proto.handleMessage(msg_name_3);
}

/**************************************************************************************************/

TEST(MackieProtocol, RecArm)
{
    midixer::MockMidixerCbs mock_midixer;
    MackieProtocol mackie_proto(&mock_midixer);

    // Declare expectations
    EXPECT_CALL(mock_midixer, updateTrackName(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateRecArm(1, true)).Times(1);
    EXPECT_CALL(mock_midixer, updateRecArm(2, true)).Times(1);
    EXPECT_CALL(mock_midixer, updateRecArm(3, false)).Times(1);
    EXPECT_CALL(mock_midixer, updateRecArm(4, false)).Times(1);
    EXPECT_CALL(mock_midixer, updateSolo(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateMute(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateFaderPosition(_, _)).Times(0);

    // Create messages
    MidiMcuMsg arm_1_en({midi::MSG_TYPE_NOTE_ON << 4, NOTE_REC_1, 0x01});
    MidiMcuMsg arm_2_en({midi::MSG_TYPE_NOTE_ON << 4, NOTE_REC_2, 0x01});
    MidiMcuMsg arm_3_dis({midi::MSG_TYPE_NOTE_ON << 4, NOTE_REC_3, 0x00});
    MidiMcuMsg arm_4_dis({midi::MSG_TYPE_NOTE_ON << 4, NOTE_REC_4, 0x00});

    // Call handling
    mackie_proto.handleMessage(arm_1_en);
    mackie_proto.handleMessage(arm_2_en);
    mackie_proto.handleMessage(arm_3_dis);
    mackie_proto.handleMessage(arm_4_dis);
}

/**************************************************************************************************/

TEST(MackieProtocol, Solo)
{
    midixer::MockMidixerCbs mock_midixer;
    MackieProtocol mackie_proto(&mock_midixer);

    // Declare expectations
    EXPECT_CALL(mock_midixer, updateTrackName(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateRecArm(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateSolo(1, true)).Times(1);
    EXPECT_CALL(mock_midixer, updateSolo(3, false)).Times(1);
    EXPECT_CALL(mock_midixer, updateSolo(5, true)).Times(1);
    EXPECT_CALL(mock_midixer, updateSolo(7, false)).Times(1);
    EXPECT_CALL(mock_midixer, updateMute(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateFaderPosition(_, _)).Times(0);

    // Create messages
    MidiMcuMsg solo_1_en({midi::MSG_TYPE_NOTE_ON << 4, NOTE_SOLO_1, 0x01});
    MidiMcuMsg solo_3_dis({midi::MSG_TYPE_NOTE_ON << 4, NOTE_SOLO_3, 0x00});
    MidiMcuMsg solo_5_en({midi::MSG_TYPE_NOTE_ON << 4, NOTE_SOLO_5, 0x01});
    MidiMcuMsg solo_7_dis({midi::MSG_TYPE_NOTE_ON << 4, NOTE_SOLO_7, 0x00});

    // Call handling
    mackie_proto.handleMessage(solo_1_en);
    mackie_proto.handleMessage(solo_3_dis);
    mackie_proto.handleMessage(solo_5_en);
    mackie_proto.handleMessage(solo_7_dis);
}

/**************************************************************************************************/

TEST(MackieProtocol, Mute)
{
    midixer::MockMidixerCbs mock_midixer;
    MackieProtocol mackie_proto(&mock_midixer);

    // Declare expectations
    EXPECT_CALL(mock_midixer, updateTrackName(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateRecArm(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateSolo(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateMute(1, true)).Times(1);
    EXPECT_CALL(mock_midixer, updateMute(2, true)).Times(1);
    EXPECT_CALL(mock_midixer, updateMute(3, false)).Times(1);
    EXPECT_CALL(mock_midixer, updateMute(4, false)).Times(1);
    EXPECT_CALL(mock_midixer, updateFaderPosition(_, _)).Times(0);

    // Create messages
    MidiMcuMsg mute_1_en({midi::MSG_TYPE_NOTE_ON << 4, NOTE_MUTE_1, 0x01});
    MidiMcuMsg mute_2_en({midi::MSG_TYPE_NOTE_ON << 4, NOTE_MUTE_2, 0x01});
    MidiMcuMsg mute_3_dis({midi::MSG_TYPE_NOTE_ON << 4, NOTE_MUTE_3, 0x00});
    MidiMcuMsg mute_4_dis({midi::MSG_TYPE_NOTE_ON << 4, NOTE_MUTE_4, 0x00});

    // Call handling
    mackie_proto.handleMessage(mute_1_en);
    mackie_proto.handleMessage(mute_2_en);
    mackie_proto.handleMessage(mute_3_dis);
    mackie_proto.handleMessage(mute_4_dis);
}

/**************************************************************************************************/

TEST(MackieProtocol, FaderPosition)
{
    midixer::MockMidixerCbs mock_midixer;
    MackieProtocol mackie_proto(&mock_midixer);

    // Declare expectations
    EXPECT_CALL(mock_midixer, updateTrackName(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateRecArm(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateSolo(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateMute(_, _)).Times(0);
    EXPECT_CALL(mock_midixer, updateFaderPosition(1, 0)).Times(1); // Min
    EXPECT_CALL(mock_midixer, updateFaderPosition(2, 16380)).Times(1); // 1st quarter
    EXPECT_CALL(mock_midixer, updateFaderPosition(3, 32764)).Times(1); // Adjusted Middle
    EXPECT_CALL(mock_midixer, updateFaderPosition(6, 49148)).Times(1); // Adjusted 3rd quarter
    EXPECT_CALL(mock_midixer, updateFaderPosition(7, 65532)).Times(1); // Adjusted Max

    // Create messages
    MidiMcuMsg fader_pos_1({(midi::MSG_TYPE_PITCH_BEND << 4) + 0, 0x00, 0x00}); // Min
    MidiMcuMsg fader_pos_2({(midi::MSG_TYPE_PITCH_BEND << 4) + 1, 0x7F, 0x1F}); // 1st quarter
    MidiMcuMsg fader_pos_3({(midi::MSG_TYPE_PITCH_BEND << 4) + 2, 0x7F, 0x3F}); // Middle
    MidiMcuMsg fader_pos_6({(midi::MSG_TYPE_PITCH_BEND << 4) + 5, 0x7F, 0x5F}); // 3rd quarter
    MidiMcuMsg fader_pos_7({(midi::MSG_TYPE_PITCH_BEND << 4) + 6, 0x7F, 0x7F}); // Max

    // Call handling
    mackie_proto.handleMessage(fader_pos_1);
    mackie_proto.handleMessage(fader_pos_2);
    mackie_proto.handleMessage(fader_pos_3);
    mackie_proto.handleMessage(fader_pos_6);
    mackie_proto.handleMessage(fader_pos_7);
}