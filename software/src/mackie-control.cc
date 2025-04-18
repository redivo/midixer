/**************************************************************************************************/
/**
 * \file   mackie-control.cc
 * \brief  Implementation of Mackie Control Protocol based on MIDI messages
 *
 * This file was written based on information of these two references:
 *   https://github.com/NicoG60/TouchMCU/blob/main/doc/mackie_control_protocol.md
 *   https://github.com/silveirago/Faduino
 */
/**************************************************************************************************/

#include "mackie-control.h"

#include <stdio.h>

namespace mcu {

/**************************************************************************************************/
/* MidiMCU                                                                                        */
/**************************************************************************************************/

MidiMCU::MidiMCU(midi::midi_msg_t message) : midi::MidiMsg(message)
{
}

/**************************************************************************************************/

bool MidiMCU::isVpotRotation()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            getRawMidiChannel() == 0 &&
            getControl() >= CC_VPOT_1_ROTATION &&
            getControl() <= CC_VPOT_8_ROTATION);
}

/**************************************************************************************************/

bool MidiMCU::isExternalControl()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            getRawMidiChannel() == 0 &&
            getControl() == CC_EXTERNAL_CONTROL);
}

/**************************************************************************************************/

bool MidiMCU::isVpotLedRing()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            getRawMidiChannel() == 0 &&
            getControl() >= CC_VPOT_1_LED_RING &&
            getControl() <= CC_VPOT_8_LED_RING);
}

/**************************************************************************************************/

bool MidiMCU::isJogWheel()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            getRawMidiChannel() == 0 &&
            getControl() == CC_JOG_WHEEL);
}

/**************************************************************************************************/

bool MidiMCU::isTimecodeDigit()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            (getRawMidiChannel() == 0 || getRawMidiChannel() == 15) &&
            getControl() >= CC_TIMECODE_DIGIT_1 &&
            getControl() <= CC_TIMECODE_DIGIT_10);
}

/**************************************************************************************************/

bool MidiMCU::isAssignmentDigit()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            (getRawMidiChannel() == 0 || getRawMidiChannel() == 15) &&
            getControl() >= CC_ASSIGNMENT_DIGIT_1 &&
            getControl() <= CC_ASSIGNMENT_DIGIT_2);
}

/**************************************************************************************************/

bool MidiMCU::isRec()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_REC_1 &&
            getRawNote() <= NOTE_REC_8);
}

/**************************************************************************************************/

bool MidiMCU::isSolo()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SOLO_1 &&
            getRawNote() <= NOTE_SOLO_8);
}

/**************************************************************************************************/

bool MidiMCU::isMute()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_MUTE_1 &&
            getRawNote() <= NOTE_MUTE_8);
}

/**************************************************************************************************/

bool MidiMCU::isSelect()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SELECT_1 &&
            getRawNote() <= NOTE_SELECT_8);
}

/**************************************************************************************************/

bool MidiMCU::isVpotSwitch()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_VPOT_SWITCH_1 &&
            getRawNote() <= NOTE_VPOT_SWITCH_8);
}

/**************************************************************************************************/

bool MidiMCU::isVpotAssignment()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_ASSIGN_TRACK &&
            getRawNote() <= NOTE_ASSIGN_INSTRUMENT);
}

/**************************************************************************************************/

bool MidiMCU::isFadersBank()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_BANK_LEFT &&
            getRawNote() <= NOTE_GLOBAL);
}

/**************************************************************************************************/

bool MidiMCU::isDisplay()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_NAME_VAL_BUTTON &&
            getRawNote() <= NOTE_SMPTE_BEATS_BUTTON);
}

/**************************************************************************************************/

bool MidiMCU::isFunctionSelection()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_F1 &&
            getRawNote() <= NOTE_F8);
}

/**************************************************************************************************/

bool MidiMCU::isGlobalView()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_MIDI_TRACKS &&
            getRawNote() <= NOTE_USER);
}

/**************************************************************************************************/

bool MidiMCU::isModifier()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SHIFT &&
            getRawNote() <= NOTE_ALT);
}

/**************************************************************************************************/

bool MidiMCU::isAutomation()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_READ_OFF &&
            getRawNote() <= NOTE_GROUP);
}

/**************************************************************************************************/

bool MidiMCU::isUtilities()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SAVE &&
            getRawNote() <= NOTE_ENTER);
}

/**************************************************************************************************/

bool MidiMCU::isOther()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_MARKERS &&
            getRawNote() <= NOTE_SOLO);
}

/**************************************************************************************************/

bool MidiMCU::isTranspot()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_REWIND &&
            getRawNote() <= NOTE_RECORD);
}

/**************************************************************************************************/

bool MidiMCU::isNavigation()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_UP &&
            getRawNote() <= NOTE_SCRUB);
}

/**************************************************************************************************/

bool MidiMCU::isUserSwitch()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_USER_SWITCH_1 &&
            getRawNote() <= NOTE_USER_SWITCH_2);
}

/**************************************************************************************************/

bool MidiMCU::isFaderTouched()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_FADER_1_TOUCHED &&
            getRawNote() <= NOTE_MASTER_FADER_TOUCHED);
}

/**************************************************************************************************/

bool MidiMCU::isLed()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SMPTE_LED &&
            getRawNote() <= NOTE_RUDE_SOLO_LED);
}

/**************************************************************************************************/

bool MidiMCU::isRelayClick()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() == NOTE_RELAY_CLICK);
}

/**************************************************************************************************/

bool MidiMCU::isFaderPosition()
{
    return (getMsgType() == midi::MSG_TYPE_PITCH_BEND);
}

/**************************************************************************************************/

cc_control_t MidiMCU::getControl()
{
    int control = midi::MidiMsg::getControl();

    switch (control) {
        case CC_VPOT_1_ROTATION:
        case CC_VPOT_2_ROTATION:
        case CC_VPOT_3_ROTATION:
        case CC_VPOT_4_ROTATION:
        case CC_VPOT_5_ROTATION:
        case CC_VPOT_6_ROTATION:
        case CC_VPOT_7_ROTATION:
        case CC_VPOT_8_ROTATION:
        case CC_EXTERNAL_CONTROL:
        case CC_VPOT_1_LED_RING:
        case CC_VPOT_2_LED_RING:
        case CC_VPOT_3_LED_RING:
        case CC_VPOT_4_LED_RING:
        case CC_VPOT_5_LED_RING:
        case CC_VPOT_6_LED_RING:
        case CC_VPOT_7_LED_RING:
        case CC_VPOT_8_LED_RING:
        case CC_JOG_WHEEL:
            // These controls are valid for Midi channel 0 only
            if (getRawMidiChannel() == 0) {
                return static_cast<cc_control_t>(control);
            }
            break;

        case CC_TIMECODE_DIGIT_1:
        case CC_TIMECODE_DIGIT_2:
        case CC_TIMECODE_DIGIT_3:
        case CC_TIMECODE_DIGIT_4:
        case CC_TIMECODE_DIGIT_5:
        case CC_TIMECODE_DIGIT_6:
        case CC_TIMECODE_DIGIT_7:
        case CC_TIMECODE_DIGIT_8:
        case CC_TIMECODE_DIGIT_9:
        case CC_TIMECODE_DIGIT_10:
        case CC_ASSIGNMENT_DIGIT_1:
        case CC_ASSIGNMENT_DIGIT_2:
            // These controls are valid for Midi channels 0 and 15 only
            if (getRawMidiChannel() == 0 || getRawMidiChannel() == 15) {
                return static_cast<cc_control_t>(control);
            }
            break;

        default:
            return CC_UNKNOWN;
    }

    return CC_UNKNOWN;
}

/**************************************************************************************************/

const char* MidiMCU::getString()
{
    static char out[MIDI_MSG_MAX_STRING_SIZE];

    if (isVpotRotation()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuVpotRotation *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isExternalControl()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuExternalControl *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isVpotLedRing()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuVpotLedRing *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isJogWheel()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuJogWheel *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isTimecodeDigit()) {
        return "";
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuTimecodeDigit *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isAssignmentDigit()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuAssignmentDigit *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isRec()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuRec *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isSolo()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuSolo *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isMute()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuMute *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isSelect()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuSelect *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isVpotSwitch()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuVpotSwitch *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isVpotAssignment()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuVpotAssignment *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isFadersBank()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuFadersBank *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isDisplay()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuDisplay *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isFunctionSelection()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuFunctionSelection *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isGlobalView()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuGlobalView *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isModifier()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuModifier *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isAutomation()) {
        return "";
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuAutomation *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isUtilities()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuUtilities *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isOther()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuOther *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isTranspot()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuTranspot *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isNavigation()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuNavigation *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isUserSwitch()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuUserSwitch *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isFaderTouched()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuFaderTouched *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isLed()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuLed *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isRelayClick()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuRelayClick *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (isFaderPosition()) {
        sprintf(out, "==============================\r\n"
                    "%s\r\n"
                    "%s\r\n", static_cast<MidiMcuFaderPosition *>(this)->getString(),
                    getRawDataString());
        return out;
    }

    else if (midi::MidiMsg::getMsgType() == midi::MSG_TYPE_CHANNEL_PRESSURE) {
        // TODO VU meter
        return "";
    }

    else {
        return MidiMsg::getString();
    }
}
#if 0
char getTimecodeChar() {
    return static_cast<char>(raw_data_.byte3);
}
String getStringUnknownOnly()
{
    return getString(false);
}
};
#endif

/**************************************************************************************************/
/* MidiMcuVpotRotation */
/**************************************************************************************************/
MidiMcuVpotRotation::MidiMcuVpotRotation(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuVpotRotation::getString()
{
    return "VpotRotation";
}

/**************************************************************************************************/
/* MidiMcuExternalControl */
/**************************************************************************************************/
MidiMcuExternalControl::MidiMcuExternalControl(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuExternalControl::getString()
{
    return "ExternalControl";
}

/**************************************************************************************************/
/* MidiMcuVpotLedRing */
/**************************************************************************************************/
MidiMcuVpotLedRing::MidiMcuVpotLedRing(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuVpotLedRing::getString()
{
    return "VpotLedRing";
}

/**************************************************************************************************/
/* MidiMcuJogWheel */
/**************************************************************************************************/
MidiMcuJogWheel::MidiMcuJogWheel(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuJogWheel::getString()
{
    return "JogWheel";
}

/**************************************************************************************************/
/* MidiMcuTimecodeDigit */
/**************************************************************************************************/
MidiMcuTimecodeDigit::MidiMcuTimecodeDigit(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuTimecodeDigit::getString()
{
    return "TimecodeDigit";
}

/**************************************************************************************************/
/* MidiMcuAssignmentDigit */
/**************************************************************************************************/
MidiMcuAssignmentDigit::MidiMcuAssignmentDigit(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuAssignmentDigit::getString()
{
    return "AssignmentDigit";
}

/**************************************************************************************************/
/* MidiMcuRec */
/**************************************************************************************************/
MidiMcuRec::MidiMcuRec(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuRec::getString()
{
    return "Rec";
}

/**************************************************************************************************/
/* MidiMcuSolo */
/**************************************************************************************************/
MidiMcuSolo::MidiMcuSolo(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuSolo::getString()
{
    return "Solo";
}

/**************************************************************************************************/
/* MidiMcuMute */
/**************************************************************************************************/
MidiMcuMute::MidiMcuMute(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuMute::getString()
{
    return "Mute";
}

/**************************************************************************************************/
/* MidiMcuSelect */
/**************************************************************************************************/
MidiMcuSelect::MidiMcuSelect(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuSelect::getString()
{
    return "Select";
}

/**************************************************************************************************/
/* MidiMcuVpotSwitch */
/**************************************************************************************************/
MidiMcuVpotSwitch::MidiMcuVpotSwitch(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuVpotSwitch::getString()
{
    return "VpotSwitch";
}

/**************************************************************************************************/
/* MidiMcuVpotAssignment */
/**************************************************************************************************/
MidiMcuVpotAssignment::MidiMcuVpotAssignment(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuVpotAssignment::getString()
{
    return "VpotAssignment";
}

/**************************************************************************************************/
/* MidiMcuFadersBank */
/**************************************************************************************************/
MidiMcuFadersBank::MidiMcuFadersBank(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuFadersBank::getString()
{
    return "FadersBank";
}

/**************************************************************************************************/
/* MidiMcuDisplay */
/**************************************************************************************************/
MidiMcuDisplay::MidiMcuDisplay(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuDisplay::getString()
{
    return "Display";
}

/**************************************************************************************************/
/* MidiMcuFunctionSelection */
/**************************************************************************************************/
MidiMcuFunctionSelection::MidiMcuFunctionSelection(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuFunctionSelection::getString()
{
    return "FunctionSelection";
}

/**************************************************************************************************/
/* MidiMcuGlobalView */
/**************************************************************************************************/
MidiMcuGlobalView::MidiMcuGlobalView(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuGlobalView::getString()
{
    return "GlobalView";
}

/**************************************************************************************************/
/* MidiMcuModifier */
/**************************************************************************************************/
MidiMcuModifier::MidiMcuModifier(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuModifier::getString()
{
    return "Modifier";
}

/**************************************************************************************************/
/* MidiMcuAutomation */
/**************************************************************************************************/
MidiMcuAutomation::MidiMcuAutomation(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuAutomation::getString()
{
    return "Automation";
}

/**************************************************************************************************/
/* MidiMcuUtilities */
/**************************************************************************************************/
MidiMcuUtilities::MidiMcuUtilities(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuUtilities::getString()
{
    return "Utilities";
}

/**************************************************************************************************/
/* MidiMcuOther */
/**************************************************************************************************/
MidiMcuOther::MidiMcuOther(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuOther::getString()
{
    return "Other";
}

/**************************************************************************************************/
/* MidiMcuTranspot */
/**************************************************************************************************/
MidiMcuTranspot::MidiMcuTranspot(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuTranspot::getString()
{
    return "Transpot";
}

/**************************************************************************************************/
/* MidiMcuNavigation */
/**************************************************************************************************/
MidiMcuNavigation::MidiMcuNavigation(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuNavigation::getString()
{
    return "Navigation";
}

/**************************************************************************************************/
/* MidiMcuUserSwitch */
/**************************************************************************************************/
MidiMcuUserSwitch::MidiMcuUserSwitch(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuUserSwitch::getString()
{
    return "UserSwitch";
}

/**************************************************************************************************/
/* MidiMcuFaderTouched */
/**************************************************************************************************/
MidiMcuFaderTouched::MidiMcuFaderTouched(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuFaderTouched::getString()
{
    return "FaderTouched";
}

/**************************************************************************************************/
/* MidiMcuLed */
/**************************************************************************************************/
MidiMcuLed::MidiMcuLed(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuLed::getString()
{
    return "Led";
}

/**************************************************************************************************/
/* MidiMcuRelayClick */
/**************************************************************************************************/
MidiMcuRelayClick::MidiMcuRelayClick(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuRelayClick::getString()
{
    return "RelayClick";
}

/**************************************************************************************************/
/* MidiMcuFaderPosition */
/**************************************************************************************************/
MidiMcuFaderPosition::MidiMcuFaderPosition(midi::midi_msg_t message) : MidiMCU(message)
{
}

/**************************************************************************************************/

const char* MidiMcuFaderPosition::getString()
{
    return "FaderPosition";
}

/**************************************************************************************************/
/* MackieProtocol                                                                                 */
/**************************************************************************************************/

void MackieProtocol::handleMessage(MidiMCU message)
{
    // It could be the first system message
    if (!system_message_handling_ && message.getMsgType() == midi::MSG_TYPE_SYSTEM) {
        // Inform we started to handle a system message.
        // It could have many messages
        system_message_handling_ = true;
        system_messages_count_ = 1;
        return;
    }

    if (system_message_handling_) {
        system_messages_count_++;

        // The second message is the identification
        if (system_messages_count_ == 2 && m)
    }

    if (message.isVpotRotation()) {
        // TODO - Not implemented yet
    }

    else if (message.isExternalControl()) {
        // TODO - Not implemented yet
    }

    else if (message.isVpotLedRing()) {
        // TODO - Not implemented yet
    }

    else if (message.isJogWheel()) {
        // TODO - Not implemented yet
    }

    else if (message.isTimecodeDigit()) {
        // TODO - Not implemented yet
    }

    else if (message.isAssignmentDigit()) {
        // TODO - Not implemented yet
    }

    else if (message.isRec()) {
        // REC is in Notes message type
        tracks_[message.getRawNote() - NOTE_REC_1].setArm(!!message.getRawVelocity());
    }

    else if (message.isSolo()) {
        // REC is in Notes message type
        tracks_[message.getRawNote() - NOTE_SOLO_1].setSolo(!!message.getRawVelocity());
    }

    else if (message.isMute()) {
        // REC is in Notes message type
        tracks_[message.getRawNote() - NOTE_MUTE_1].setMute(!!message.getRawVelocity());
    }

    else if (message.isSelect()) {
        // TODO - Not implemented yet
    }

    else if (message.isVpotSwitch()) {
        // TODO - Not implemented yet
    }

    else if (message.isVpotAssignment()) {
        // TODO - Not implemented yet
    }

    else if (message.isFadersBank()) {
        // TODO - Not implemented yet
    }

    else if (message.isDisplay()) {
        // TODO - Not implemented yet
    }

    else if (message.isFunctionSelection()) {
        // TODO - Not implemented yet
    }

    else if (message.isGlobalView()) {
        // TODO - Not implemented yet
    }

    else if (message.isModifier()) {
        // TODO - Not implemented yet
    }

    else if (message.isAutomation()) {
        // TODO - Not implemented yet
    }

    else if (message.isUtilities()) {
        // TODO - Not implemented yet
    }

    else if (message.isOther()) {
        // TODO - Not implemented yet
    }

    else if (message.isTranspot()) {
        // TODO - Not implemented yet
    }

    else if (message.isNavigation()) {
        // TODO - Not implemented yet
    }

    else if (message.isUserSwitch()) {
        // TODO - Not implemented yet
    }

    else if (message.isFaderTouched()) {
        // TODO - Not implemented yet
    }

    else if (message.isLed()) {
        // TODO - Not implemented yet
    }

    else if (message.isRelayClick()) {
        // TODO - Not implemented yet
    }

    else if (message.isFaderPosition()) {
        // TODO - Not implemented yet
    }
}

}  // namespace mcu
