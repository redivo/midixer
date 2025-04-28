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
#include <string.h>

namespace mcu {

/**************************************************************************************************/
/* MidiMcuMsg                                                                                        */
/**************************************************************************************************/

MidiMcuMsg::MidiMcuMsg(midi::midi_msg_t message) : midi::MidiMsg(message)
{
}

/**************************************************************************************************/

bool MidiMcuMsg::isVpotRotation()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            getRawMidiChannel() == 0 &&
            getControl() >= CC_VPOT_1_ROTATION &&
            getControl() <= CC_VPOT_8_ROTATION);
}

/**************************************************************************************************/

bool MidiMcuMsg::isExternalControl()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            getRawMidiChannel() == 0 &&
            getControl() == CC_EXTERNAL_CONTROL);
}

/**************************************************************************************************/

bool MidiMcuMsg::isVpotLedRing()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            getRawMidiChannel() == 0 &&
            getControl() >= CC_VPOT_1_LED_RING &&
            getControl() <= CC_VPOT_8_LED_RING);
}

/**************************************************************************************************/

bool MidiMcuMsg::isJogWheel()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            getRawMidiChannel() == 0 &&
            getControl() == CC_JOG_WHEEL);
}

/**************************************************************************************************/

bool MidiMcuMsg::isTimecodeDigit()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            (getRawMidiChannel() == 0 || getRawMidiChannel() == 15) &&
            getControl() >= CC_TIMECODE_DIGIT_1 &&
            getControl() <= CC_TIMECODE_DIGIT_10);
}

/**************************************************************************************************/

bool MidiMcuMsg::isAssignmentDigit()
{
    return (getMsgType() == midi::MSG_TYPE_CONTROL_CHANGE &&
            (getRawMidiChannel() == 0 || getRawMidiChannel() == 15) &&
            getControl() >= CC_ASSIGNMENT_DIGIT_1 &&
            getControl() <= CC_ASSIGNMENT_DIGIT_2);
}

/**************************************************************************************************/

bool MidiMcuMsg::isRec()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_REC_1 &&
            getRawNote() <= NOTE_REC_8);
}

/**************************************************************************************************/

bool MidiMcuMsg::isSolo()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SOLO_1 &&
            getRawNote() <= NOTE_SOLO_8);
}

/**************************************************************************************************/

bool MidiMcuMsg::isMute()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_MUTE_1 &&
            getRawNote() <= NOTE_MUTE_8);
}

/**************************************************************************************************/

bool MidiMcuMsg::isSelect()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SELECT_1 &&
            getRawNote() <= NOTE_SELECT_8);
}

/**************************************************************************************************/

bool MidiMcuMsg::isVpotSwitch()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_VPOT_SWITCH_1 &&
            getRawNote() <= NOTE_VPOT_SWITCH_8);
}

/**************************************************************************************************/

bool MidiMcuMsg::isVpotAssignment()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_ASSIGN_TRACK &&
            getRawNote() <= NOTE_ASSIGN_INSTRUMENT);
}

/**************************************************************************************************/

bool MidiMcuMsg::isFadersBank()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_BANK_LEFT &&
            getRawNote() <= NOTE_GLOBAL);
}

/**************************************************************************************************/

bool MidiMcuMsg::isDisplay()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_NAME_VAL_BUTTON &&
            getRawNote() <= NOTE_SMPTE_BEATS_BUTTON);
}

/**************************************************************************************************/

bool MidiMcuMsg::isFunctionSelection()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_F1 &&
            getRawNote() <= NOTE_F8);
}

/**************************************************************************************************/

bool MidiMcuMsg::isGlobalView()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_MIDI_TRACKS &&
            getRawNote() <= NOTE_USER);
}

/**************************************************************************************************/

bool MidiMcuMsg::isModifier()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SHIFT &&
            getRawNote() <= NOTE_ALT);
}

/**************************************************************************************************/

bool MidiMcuMsg::isAutomation()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_READ_OFF &&
            getRawNote() <= NOTE_GROUP);
}

/**************************************************************************************************/

bool MidiMcuMsg::isUtilities()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SAVE &&
            getRawNote() <= NOTE_ENTER);
}

/**************************************************************************************************/

bool MidiMcuMsg::isOther()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_MARKERS &&
            getRawNote() <= NOTE_SOLO);
}

/**************************************************************************************************/

bool MidiMcuMsg::isTransport()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_REWIND &&
            getRawNote() <= NOTE_RECORD);
}

/**************************************************************************************************/

bool MidiMcuMsg::isNavigation()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_UP &&
            getRawNote() <= NOTE_SCRUB);
}

/**************************************************************************************************/

bool MidiMcuMsg::isUserSwitch()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_USER_SWITCH_1 &&
            getRawNote() <= NOTE_USER_SWITCH_2);
}

/**************************************************************************************************/

bool MidiMcuMsg::isFaderTouched()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_FADER_1_TOUCHED &&
            getRawNote() <= NOTE_MASTER_FADER_TOUCHED);
}

/**************************************************************************************************/

bool MidiMcuMsg::isLed()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() >= NOTE_SMPTE_LED &&
            getRawNote() <= NOTE_RUDE_SOLO_LED);
}

/**************************************************************************************************/

bool MidiMcuMsg::isRelayClick()
{
    return (getMsgType() == midi::MSG_TYPE_NOTE_ON &&
            getRawMidiChannel() == 0 &&
            getRawNote() == NOTE_RELAY_CLICK);
}

/**************************************************************************************************/

bool MidiMcuMsg::isFaderPosition()
{
    return (getMsgType() == midi::MSG_TYPE_PITCH_BEND);
}

/**************************************************************************************************/

bool MidiMcuMsg::isMeter()
{
    return (midi::MidiMsg::getMsgType() == midi::MSG_TYPE_CHANNEL_PRESSURE);
}


/**************************************************************************************************/

cc_control_t MidiMcuMsg::getControl()
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

msg_group_t MidiMcuMsg::getMsgGroup()
{
    if (isVpotRotation()) {
        return MSG_GROUP_VPOT_ROTATION;
    }
    if (isExternalControl()) {
        return MSG_GROUP_EXTERNAL_CONTROL;
    }
    if (isVpotLedRing()) {
        return MSG_GROUP_VPOT_LED_RING;
    }
    if (isJogWheel()) {
        return MSG_GROUP_JOG_WHEEL;
    }
    if (isTimecodeDigit()) {
        return MSG_GROUP_TIMECODE_DIGIT;
    }
    if (isAssignmentDigit()) {
        return MSG_GROUP_ASSIGNMENT_DIGIT;
    }
    if (isRec()) {
        return MSG_GROUP_REC;
    }
    if (isSolo()) {
        return MSG_GROUP_SOLO;
    }
    if (isMute()) {
        return MSG_GROUP_MUTE;
    }
    if (isSelect()) {
        return MSG_GROUP_SELECT;
    }
    if (isVpotSwitch()) {
        return MSG_GROUP_VPOT_SWITCH;
    }
    if (isVpotAssignment()) {
        return MSG_GROUP_VPOT_ASSIGNMENT;
    }
    if (isFadersBank()) {
        return MSG_GROUP_FADERS_BANK;
    }
    if (isDisplay()) {
        return MSG_GROUP_DISPLAY;
    }
    if (isFunctionSelection()) {
        return MSG_GROUP_FUNCTION_SELECTION;
    }
    if (isGlobalView()) {
        return MSG_GROUP_GLOBAL_VIEW;
    }
    if (isModifier()) {
        return MSG_GROUP_MODIFIER;
    }
    if (isAutomation()) {
        return MSG_GROUP_AUTOMATION;
    }
    if (isUtilities()) {
        return MSG_GROUP_UTILITIES;
    }
    if (isOther()) {
        return MSG_GROUP_OTHER;
    }
    if (isTransport()) {
        return MSG_GROUP_TRANSPORT;
    }
    if (isNavigation()) {
        return MSG_GROUP_NAVIGATION;
    }
    if (isUserSwitch()) {
        return MSG_GROUP_USER_SWITCH;
    }
    if (isFaderTouched()) {
        return MSG_GROUP_FADER_TOUCHED;
    }
    if (isLed()) {
        return MSG_GROUP_LED;
    }
    if (isRelayClick()) {
        return MSG_GROUP_RELAY_CLICK;
    }
    if (isFaderPosition()) {
        return MSG_GROUP_FADER_POSITION;
    }
    if (isMeter()) {
        return MSG_GROUP_METER;
    }

    return MSG_GROUP_UNKNOWN;
}

/**************************************************************************************************/

const char* MidiMcuMsg::getString()
{
    static char out[MIDI_MSG_MAX_STRING_SIZE];
    char name[MAX_MESSAGE_GROUP_NAME_SIZE];

    /**********************************************************************************************/
    /* Copy Message description name                                                              */
    /**********************************************************************************************/
    switch (getMsgGroup()) {
        case MSG_GROUP_VPOT_ROTATION:
            strcpy(name, "VPOT ROT");
            break;
        case MSG_GROUP_EXTERNAL_CONTROL:
            strcpy(name, "EXT CTRL");
            break;
        case MSG_GROUP_VPOT_LED_RING:
            strcpy(name, "VPOT LED");
            break;
        case MSG_GROUP_JOG_WHEEL:
            strcpy(name, "JOG WHEEL");
            break;
        case MSG_GROUP_TIMECODE_DIGIT:
            strcpy(name, "TIMECODE DIGIT");
            break;
        case MSG_GROUP_ASSIGNMENT_DIGIT:
            strcpy(name, "ASSIGN DIGIT");
            break;
        case MSG_GROUP_REC:
            strcpy(name, "REC");
            break;
        case MSG_GROUP_SOLO:
            strcpy(name, "SOLO");
            break;
        case MSG_GROUP_MUTE:
            strcpy(name, "MUTE");
            break;
        case MSG_GROUP_SELECT:
            strcpy(name, "SEL");
            break;
        case MSG_GROUP_VPOT_SWITCH:
            strcpy(name, "VPOT SW");
            break;
        case MSG_GROUP_VPOT_ASSIGNMENT:
            strcpy(name, "VPOT ASSIGN");
            break;
        case MSG_GROUP_FADERS_BANK:
            strcpy(name, "FADER BANK");
            break;
        case MSG_GROUP_DISPLAY:
            strcpy(name, "DISPLAY");
            break;
        case MSG_GROUP_FUNCTION_SELECTION:
            strcpy(name, "FUNC SEL");
            break;
        case MSG_GROUP_GLOBAL_VIEW:
            strcpy(name, "GLOB VIEW");
            break;
        case MSG_GROUP_MODIFIER:
            strcpy(name, "MOD");
            break;
        case MSG_GROUP_AUTOMATION:
            strcpy(name, "AUTO");
            break;
        case MSG_GROUP_UTILITIES:
            strcpy(name, "UTILS");
            break;
        case MSG_GROUP_OTHER:
            strcpy(name, "OTHER");
            break;
        case MSG_GROUP_TRANSPORT:
            strcpy(name, "TRANSPORT");
            break;
        case MSG_GROUP_NAVIGATION:
            strcpy(name, "NAV");
            break;
        case MSG_GROUP_USER_SWITCH:
            strcpy(name, "USR SW");
            break;
        case MSG_GROUP_FADER_TOUCHED:
            strcpy(name, "FADER TCHD");
            break;
        case MSG_GROUP_LED:
            strcpy(name, "LED");
            break;
        case MSG_GROUP_RELAY_CLICK:
            strcpy(name, "RLY CLICK");
            break;
        case MSG_GROUP_FADER_POSITION:
            strcpy(name, "FADER POS");
            break;
        case MSG_GROUP_METER:
            strcpy(name, "METER");
            break;
        default:
            strcpy(name, "UNKNOWN");
            break;
    }

    /**********************************************************************************************/
    /* Mount out message                                                                          */
    /**********************************************************************************************/
    sprintf(out, "==============================\r\n"
                "%s\r\n"
                "%s\r\n", name,
                getRawDataString());
    return out;
}

}  // namespace mcu