/**************************************************************************************************/
/**
 * \file   test-mcu-sys-msg-fsm.cc
 * \brief  Tests for Mackie Control Protocol System Message FSM
 */
/**************************************************************************************************/

#include <gtest/gtest.h>
#include "proto-mcu/sys-msg-fsm.h"

using namespace mcu;

/**************************************************************************************************/

TEST(McuSystemMsgFsm, Constructor)
{
    McuSystemMsgFsm fsm;

    // Verify initial state
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Idle);
    EXPECT_EQ(fsm.getTrackNumber(), 0);
    EXPECT_STREQ(fsm.getTrackName(), "");
}

/**************************************************************************************************/

TEST(McuSystemMsgFsm, HandleNotSystemMessage)
{
    MidiMcuMsg msg({0xB0, 0x10, 0x01});
    McuSystemMsgFsm fsm;

    // Verify that is not system message
    EXPECT_NE(msg.getMsgType(), midi::MSG_TYPE_SYSTEM);

    // Verify Idle state
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Idle);

    // Verify it was not handled
    EXPECT_FALSE(fsm.handle(msg));

    // Verify it stays in Idle state
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Idle);
}


/**************************************************************************************************/

TEST(McuSystemMsgFsm, HandleTrackName)
{
    MidiMcuMsg msg_header1({0xF0, 0x00, 0x00}); // System message
    MidiMcuMsg msg_header2({0x66, 0x14, 0x12}); // Mackie Design (0x66), Mackie Control (0x14),
                                                // Update LCD (0x12)
    MidiMcuMsg msg_name_1({0x0E, 'V', 'o'}); // Track 3 ((3 - 1) * 7 = 14 = 0x0E)
    MidiMcuMsg msg_name_2({'c', 'a', 'l'});
    MidiMcuMsg msg_name_3({'s', ' ', 0x0F7});

    McuSystemMsgFsm fsm;

    // Verify initial condition
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Idle);
    EXPECT_EQ(fsm.getTrackNumber(), 0);
    EXPECT_STREQ(fsm.getTrackName(), "");

    // Handle messages and verify states
    EXPECT_TRUE(fsm.handle(msg_header1));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Handle1st);
    EXPECT_TRUE(fsm.handle(msg_header2));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Handle2nd);
    EXPECT_TRUE(fsm.handle(msg_name_1));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::HandleLcd1st);
    EXPECT_TRUE(fsm.handle(msg_name_2));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::HandleLcdOthers);
    EXPECT_TRUE(fsm.handle(msg_name_3));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::HandleLcdLast);

    // Verify result
    EXPECT_EQ(fsm.getTrackNumber(), 3);
    EXPECT_STREQ(fsm.getTrackName(), "Vocals ");
}

/**************************************************************************************************/

TEST(McuSystemMsgFsm, HandleUnknownCommand)
{
    MidiMcuMsg msg_header1({0xF0, 0x00, 0x00}); // System message
    MidiMcuMsg msg_header2({0x66, 0x14, 0x13}); // Mackie Design (0x66), Mackie Control (0x14),
                                                // Firmware Version Request (0x13)
    MidiMcuMsg msg_dummy({0, 1, 2}); // Dummy values
    MidiMcuMsg msg_dummy_end({1, 2, 0x0F7});

    McuSystemMsgFsm fsm;

    // Verify initial condition
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Idle);
    EXPECT_EQ(fsm.getTrackNumber(), 0);
    EXPECT_STREQ(fsm.getTrackName(), "");

    // Handle messages and verify states
    EXPECT_TRUE(fsm.handle(msg_header1));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Handle1st);
    EXPECT_TRUE(fsm.handle(msg_header2));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Handle2nd);
    EXPECT_TRUE(fsm.handle(msg_dummy));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::HandleNotImplemented);
    EXPECT_TRUE(fsm.handle(msg_dummy));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::HandleNotImplemented);
    EXPECT_TRUE(fsm.handle(msg_dummy));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::HandleNotImplemented);
    EXPECT_TRUE(fsm.handle(msg_dummy_end));
    EXPECT_EQ(fsm.getState(), McuSystemMsgFsm::State::Idle);

    // Verify result
    EXPECT_EQ(fsm.getTrackNumber(), 0);
    EXPECT_STREQ(fsm.getTrackName(), "");
}