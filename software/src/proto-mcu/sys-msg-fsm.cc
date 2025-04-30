/**************************************************************************************************/
/**
 * \file   sys-msg-fsm.cc
 * \brief  Implementation of Mackie Control System Messages FSM
 *
 * This file was written based on information got through reverse engineering and by reding:
 *   https://github.com/NicoG60/TouchMCU/blob/main/doc/mackie_control_protocol.md
 */
/**************************************************************************************************/

#include "proto-mcu/sys-msg-fsm.h"
#include "string.h"

namespace mcu {

/**************************************************************************************************/
/* McuSystemMsgFsm                                                                                */
/**************************************************************************************************/

McuSystemMsgFsm::McuSystemMsgFsm()
{
    memset(track_name_, 0, sizeof(track_name_));
    memset(&last_message_, 0, sizeof(last_message_));
}

/**************************************************************************************************/

bool McuSystemMsgFsm::handle(MidiMcuMsg message)
{
    State state_before = state_;

    // Save message, calculate next state and act in this state
    last_message_ = message;
    next();
    act();

    // Return false if both before and current state are Idle, so we not not handle anything
    return !(state_before == State::Idle && state_ == State::Idle);
}

/**************************************************************************************************/

void McuSystemMsgFsm::next()
{
    switch (state_) {
        case State::Idle:
            // Go first handle state if it is a system message
            if (last_message_.getMsgType() == midi::MSG_TYPE_SYSTEM) {
                state_ = State::Handle1st;
            }
            break;

        case State::Handle1st:
            // Go to second handle state
            state_ = State::Handle2nd;
            break;

        case State::Handle2nd:
            // If it is an UpdateLCD go to HandleLcd1st, otherwise HandleNotImplemented
            if (command_id_ == Command::UpdateLCD) {
                state_ = State::HandleLcd1st;
            }
            else {
                state_ = State::HandleNotImplemented;
            }
            break;

        case State::HandleLcd1st:
            // Go to HandleLcdOthers
            state_ = State::HandleLcdOthers;
            break;

        case State::HandleLcdOthers:
            // If we reach the end of data,return to Idle
            if (last_message_.getRawData().byte3 == 0xF7) {
                state_ = State::HandleLcdLast;
            }
            break;

        case State::HandleLcdLast:
            // Go to Idle
            state_ = State::Idle;
            break;

        case State::HandleNotImplemented:
            // If we reach the end of data,return to Idle
            if (last_message_.getRawData().byte3 == 0xF7) {
                state_ = State::Idle;
            }
            break;

    }
}

/**************************************************************************************************/

void McuSystemMsgFsm::act()
{
    switch (state_) {
        case State::Idle:
            // Clear values
            manufacturer_id_ = 0;
            device_id_ = 0;
            track_num_ = 0;
            memset(track_name_, 0, sizeof(track_name_));
            track_name_index_ = 0;
            break;

        case State::Handle1st:
            manufacturer_id_ = 0;
            manufacturer_id_ |= last_message_.getRawData().byte2 << 16;
            manufacturer_id_ |= last_message_.getRawData().byte3 << 8;
            break;

        case State::Handle2nd:
            manufacturer_id_ += last_message_.getRawData().byte1;
            device_id_ = last_message_.getRawData().byte2;

            if (last_message_.getRawData().byte3 == static_cast<uint8_t>(Command::UpdateLCD)) {
                command_id_ = Command::UpdateLCD;
            }
            else {
                command_id_ = Command::Unknown;
            }
            break;

        case State::HandleLcd1st:
            // Track number, relative to managed tracks, starts in 0 and increments 7 each track
            track_num_ = (last_message_.getRawData().byte1 / 7) + 1;

            // Clear track name
            memset(track_name_, 0, sizeof(track_name_));
            track_name_index_ = 0;

            // Store first and second chars
            track_name_[track_name_index_] = last_message_.getRawData().byte2;
            track_name_index_++;
            track_name_[track_name_index_] = last_message_.getRawData().byte3;
            track_name_index_++;
            break;

        case State::HandleLcdOthers:
            // Store all bytes as chars
            track_name_[track_name_index_] = last_message_.getRawData().byte1;
            track_name_index_++;
            track_name_[track_name_index_] = last_message_.getRawData().byte2;
            track_name_index_++;
            track_name_[track_name_index_] = last_message_.getRawData().byte3;
            track_name_index_++;
            break;

        case State::HandleLcdLast:
            // The last message has only the first 2 bytes. The last one is 0xF7
            track_name_[track_name_index_] = last_message_.getRawData().byte1;
            track_name_index_++;
            track_name_[track_name_index_] = last_message_.getRawData().byte2;
            track_name_index_++;
            break;

        case State::HandleNotImplemented:
            // Nothing to do
            break;
    }
}

/**************************************************************************************************/

McuSystemMsgFsm::State McuSystemMsgFsm::getState()
{
    return state_;
}

/**************************************************************************************************/

uint8_t McuSystemMsgFsm::getTrackNumber()
{
    return track_num_;
}

/**************************************************************************************************/

const char* McuSystemMsgFsm::getTrackName()
{
    return track_name_;
}

/**************************************************************************************************/

} // namespace mcu