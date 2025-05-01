/**************************************************************************************************/
/**
 * \file   mackie-protocol.cc
 * \brief  Implementation of Mackie Control Protocol
 *
 * This file was written based on information got through reverse engineering and by reding:
 *   https://github.com/NicoG60/TouchMCU/blob/main/doc/mackie_control_protocol.md
 */
/**************************************************************************************************/

#include "proto-mcu/mackie-protocol.h"

namespace mcu {

/**************************************************************************************************/
/* MackieProtocol                                                                                 */
/**************************************************************************************************/

MackieProtocol::MackieProtocol(midixer::MidixerCbs *midixer) : midixer_(midixer)
{
}

/**************************************************************************************************/

void MackieProtocol::handleMessage(MidiMcuMsg message)
{
    // First of all we have to verify if it is a system message.
    // We can do that by calling McuSystemMsgFsm
    if (system_msg_fsm_.handle(message)) {
        // For while the only handled thing is UpdateLCD, which give us the track name and number
        if (system_msg_fsm_.getState() == McuSystemMsgFsm::State::HandleLcdLast) {
            midixer_->updateTrackName(system_msg_fsm_.getTrackNumber(), system_msg_fsm_.getTrackName());
        }

        return;
    }

    // If it is not a system message, handle it by message group
    uint8_t track;
    switch(message.getMsgGroup()) {
        case MSG_GROUP_REC:
            // REC is in Notes message type. Velocity is the value to be set
            track = message.getRawNote() - NOTE_REC_1 + 1;
            midixer_->updateRecArm(track, !!message.getRawVelocity());
            break;

        case MSG_GROUP_MUTE:
            // MUTE is in Notes message type
            track = message.getRawNote() - NOTE_MUTE_1 + 1;
            midixer_->updateMute(track, !!message.getRawVelocity());
            break;

        case MSG_GROUP_SOLO:
            // SOLO is in Notes message type
            track = message.getRawNote() - NOTE_SOLO_1 + 1;
            midixer_->updateSolo(track, !!message.getRawVelocity());
            break;

        case MSG_GROUP_FADER_POSITION: {
            // Fader position refers the track in MIDI channel (0 based)
            track = message.getRawMidiChannel() + 1;

            // The fader position range from MIDI is 0x0000:0x3FFF
            // However the fader position in MIdiXER is 0x0000:0xFFFF
            // So we have to adjust this scale
            uint16_t position = message.getRawPitchBend() * (0xFFFF/0x3FFF);
            midixer_->updateFaderPosition(track, position);
            break;
        }

        default:
            // TODO - not implemented yet
            break;
    }
}

/**************************************************************************************************/

}  // namespace mcu