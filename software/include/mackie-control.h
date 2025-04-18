/**************************************************************************************************/
/**
 * \file   mackie-control.h
 * \brief  Implementation of Mackie Control Protocol based on MIDI messages
 *
 * This file was written based on information of these two references:
 *   https://github.com/NicoG60/TouchMCU/blob/main/doc/mackie_control_protocol.md
 *   https://github.com/silveirago/Faduino
 */
/**************************************************************************************************/

#ifndef __MIDIXER_SOFTWARE_INCLUDE_MACKIE_CONTROL_H__
#define __MIDIXER_SOFTWARE_INCLUDE_MACKIE_CONTROL_H__

#include "midi-msg.h"
#include "track.h"

//!< Max number of managed tracks in original Mackie Control Protocol
#define MAX_MANAGED_TRACKS 8

namespace mcu {

/**************************************************************************************************/

// Defines for Control Change Controls
typedef enum {
    CC_UNKNOWN = -1,

    CC_VPOT_1_ROTATION = 0x10, // Valid for MIDI channel 0
    CC_VPOT_2_ROTATION = 0x11, // Valid for MIDI channel 0
    CC_VPOT_3_ROTATION = 0x12, // Valid for MIDI channel 0
    CC_VPOT_4_ROTATION = 0x13, // Valid for MIDI channel 0
    CC_VPOT_5_ROTATION = 0x14, // Valid for MIDI channel 0
    CC_VPOT_6_ROTATION = 0x18, // Valid for MIDI channel 0
    CC_VPOT_7_ROTATION = 0x16, // Valid for MIDI channel 0
    CC_VPOT_8_ROTATION = 0x17, // Valid for MIDI channel 0

    CC_EXTERNAL_CONTROL = 0x2E, // Valid for MIDI channel 0

    CC_VPOT_1_LED_RING = 0x30, // Valid for MIDI channel 0
    CC_VPOT_2_LED_RING = 0x31, // Valid for MIDI channel 0
    CC_VPOT_3_LED_RING = 0x32, // Valid for MIDI channel 0
    CC_VPOT_4_LED_RING = 0x33, // Valid for MIDI channel 0
    CC_VPOT_5_LED_RING = 0x34, // Valid for MIDI channel 0
    CC_VPOT_6_LED_RING = 0x35, // Valid for MIDI channel 0
    CC_VPOT_7_LED_RING = 0x36, // Valid for MIDI channel 0
    CC_VPOT_8_LED_RING = 0x37, // Valid for MIDI channel 0

    CC_JOG_WHEEL = 0x3C, // Valid for MIDI channel 0

    CC_TIMECODE_DIGIT_1 = 0x40, // Valid for MIDI channel 0 or 15
    CC_TIMECODE_DIGIT_2 = 0x41, // Valid for MIDI channel 0 or 15
    CC_TIMECODE_DIGIT_3 = 0x42, // Valid for MIDI channel 0 or 15
    CC_TIMECODE_DIGIT_4 = 0x43, // Valid for MIDI channel 0 or 15
    CC_TIMECODE_DIGIT_5 = 0x44, // Valid for MIDI channel 0 or 15
    CC_TIMECODE_DIGIT_6 = 0x45, // Valid for MIDI channel 0 or 15
    CC_TIMECODE_DIGIT_7 = 0x46, // Valid for MIDI channel 0 or 15
    CC_TIMECODE_DIGIT_8 = 0x47, // Valid for MIDI channel 0 or 15
    CC_TIMECODE_DIGIT_9 = 0x48, // Valid for MIDI channel 0 or 15
    CC_TIMECODE_DIGIT_10 = 0x49, // Valid for MIDI channel 0 or 15

    CC_ASSIGNMENT_DIGIT_1 = 0x4A, // Valid for MIDI channel 0 or 15
    CC_ASSIGNMENT_DIGIT_2 = 0x4B, // Valid for MIDI channel 0 or 15

} cc_control_t;

/**************************************************************************************************/

// Defines note mapping, valid for MIDI channel 0
typedef enum {
    NOTE_UNKNOWN = -1,

    NOTE_REC_1 = 0x00,
    NOTE_REC_2 = 0x01,
    NOTE_REC_3 = 0x02,
    NOTE_REC_4 = 0x03,
    NOTE_REC_5 = 0x04,
    NOTE_REC_6 = 0x05,
    NOTE_REC_7 = 0x06,
    NOTE_REC_8 = 0x07,

    NOTE_SOLO_1 = 0x08,
    NOTE_SOLO_2 = 0x09,
    NOTE_SOLO_3 = 0x0A,
    NOTE_SOLO_4 = 0x0B,
    NOTE_SOLO_5 = 0x0C,
    NOTE_SOLO_6 = 0x0D,
    NOTE_SOLO_7 = 0x0E,
    NOTE_SOLO_8 = 0x0F,

    NOTE_MUTE_1 = 0x10,
    NOTE_MUTE_2 = 0x11,
    NOTE_MUTE_3 = 0x12,
    NOTE_MUTE_4 = 0x13,
    NOTE_MUTE_5 = 0x14,
    NOTE_MUTE_6 = 0x15,
    NOTE_MUTE_7 = 0x16,
    NOTE_MUTE_8 = 0x17,

    NOTE_SELECT_1 = 0x18,
    NOTE_SELECT_2 = 0x19,
    NOTE_SELECT_3 = 0x1A,
    NOTE_SELECT_4 = 0x1B,
    NOTE_SELECT_5 = 0x1C,
    NOTE_SELECT_6 = 0x1D,
    NOTE_SELECT_7 = 0x1E,
    NOTE_SELECT_8 = 0x1F,

    NOTE_VPOT_SWITCH_1 = 0x20,
    NOTE_VPOT_SWITCH_2 = 0x21,
    NOTE_VPOT_SWITCH_3 = 0x22,
    NOTE_VPOT_SWITCH_4 = 0x23,
    NOTE_VPOT_SWITCH_5 = 0x24,
    NOTE_VPOT_SWITCH_6 = 0x25,
    NOTE_VPOT_SWITCH_7 = 0x26,
    NOTE_VPOT_SWITCH_8 = 0x27,

    NOTE_ASSIGN_TRACK = 0x28,
    NOTE_ASSIGN_SEND = 0x29,
    NOTE_ASSIGN_PAN = 0x2A,
    NOTE_ASSIGN_PLUGIN = 0x2B,
    NOTE_ASSIGN_EQ = 0x2C,
    NOTE_ASSIGN_INSTRUMENT = 0x2D,

    NOTE_BANK_LEFT = 0x2E,
    NOTE_BANK_RIGHT = 0x2F,
    NOTE_CHANNEL_LEFT = 0x30,
    NOTE_CHANNEL_RIGHT = 0x31,
    NOTE_FLIP = 0x32,
    NOTE_GLOBAL = 0x33,

    NOTE_NAME_VAL_BUTTON = 0x34,
    NOTE_SMPTE_BEATS_BUTTON = 0x35,

    NOTE_F1 = 0x36,
    NOTE_F2 = 0x37,
    NOTE_F3 = 0x38,
    NOTE_F4 = 0x39,
    NOTE_F5 = 0x3A,
    NOTE_F6 = 0x3B,
    NOTE_F7 = 0x3C,
    NOTE_F8 = 0x3D,

    NOTE_MIDI_TRACKS = 0x3E,
    NOTE_INPUTS = 0x3F,
    NOTE_AUDIO_TRACKS = 0x40,
    NOTE_AUDIO_INTRUMENTS = 0x41,
    NOTE_AUX = 0x42,
    NOTE_BUSSES = 0x43,
    NOTE_OUTPUTS = 0x44,
    NOTE_USER = 0x45,

    NOTE_SHIFT = 0x46,
    NOTE_OPTION = 0x47,
    NOTE_CONTROL = 0x48,
    NOTE_ALT = 0x49,

    NOTE_READ_OFF = 0x4A,
    NOTE_WRITE = 0x4B,
    NOTE_TRIM = 0x4C,
    NOTE_TOUCH = 0x4D,
    NOTE_LATCH = 0x4E,
    NOTE_GROUP = 0x4F,

    NOTE_SAVE = 0x50,
    NOTE_UNDO = 0x51,
    NOTE_CANCEL = 0x52,
    NOTE_ENTER = 0x53,

    NOTE_MARKERS = 0x54,
    NOTE_NUDGE = 0x55,
    NOTE_CYCLE = 0x56,
    NOTE_DROP = 0x57,
    NOTE_REPLACE = 0x58,
    NOTE_CLICK = 0x59,
    NOTE_SOLO = 0x5A,

    NOTE_REWIND = 0x5B,
    NOTE_FORWARD = 0x5C,
    NOTE_STOP = 0x5D,
    NOTE_PLAY = 0x5E,
    NOTE_RECORD = 0x5F,

    NOTE_UP = 0x60,
    NOTE_DOWN = 0x61,
    NOTE_LEFT = 0x62,
    NOTE_RIGHT = 0x63,
    NOTE_ZOOM = 0x64,
    NOTE_SCRUB = 0x65,

    NOTE_USER_SWITCH_1 = 0x66,
    NOTE_USER_SWITCH_2 = 0x67,

    NOTE_FADER_1_TOUCHED = 0x68,
    NOTE_FADER_2_TOUCHED = 0x69,
    NOTE_FADER_3_TOUCHED = 0x6A,
    NOTE_FADER_4_TOUCHED = 0x6B,
    NOTE_FADER_5_TOUCHED = 0x6C,
    NOTE_FADER_6_TOUCHED = 0x6D,
    NOTE_FADER_7_TOUCHED = 0x6E,
    NOTE_FADER_8_TOUCHED = 0x6F,
    NOTE_MASTER_FADER_TOUCHED = 0x70,

    NOTE_SMPTE_LED = 0x71,
    NOTE_BEATS_LED = 0x72,
    NOTE_RUDE_SOLO_LED = 0x73,

    NOTE_RELAY_CLICK = 0x76,

} notes_t;

/**************************************************************************************************/
/**
 * \brief  Class that defines Mackie Control Universal (MCU) MIDI Protocol
 */
class MidiMCU : public midi::MidiMsg {
   public:
    /**********************************************************************************************/
    /**
     * \brief  Constructor given an event
     * \param  event  Event to be created
     */
    MidiMCU(midi::midi_msg_t message);

    /**
     * \brief Checks if the control corresponds to a V-Pot rotation.
     * \return True if it's a V-Pot rotation, false otherwise.
     */
    bool isVpotRotation();

    /**
     * \brief Checks if the control comes from an external source.
     * \return True if it's an external control, false otherwise.
     */
    bool isExternalControl();

    /**
     * \brief Checks if the control corresponds to a V-Pot LED ring.
     * \return True if it's a V-Pot LED ring, false otherwise.
     */
    bool isVpotLedRing();

    /**
     * \brief Checks if the control is the jog wheel.
     * \return True if it's a jog wheel control, false otherwise.
     */
    bool isJogWheel();

    /**
     * \brief Checks if the control is a timecode digit.
     * \return True if it's a timecode digit, false otherwise.
     */
    bool isTimecodeDigit();

    /**
     * \brief Checks if the control is an assignment digit.
     * \return True if it's an assignment digit, false otherwise.
     */
    bool isAssignmentDigit();

    /**
     * \brief Checks if the control is a record (Rec) button.
     * \return True if it's a Rec button, false otherwise.
     */
    bool isRec();

    /**
     * \brief Checks if the control is a solo button.
     * \return True if it's a solo button, false otherwise.
     */
    bool isSolo();

    /**
     * \brief Checks if the control is a mute button.
     * \return True if it's a mute button, false otherwise.
     */
    bool isMute();

    /**
     * \brief Checks if the control is a select button.
     * \return True if it's a select button, false otherwise.
     */
    bool isSelect();

    /**
     * \brief Checks if the control is a V-Pot switch.
     * \return True if it's a V-Pot switch, false otherwise.
     */
    bool isVpotSwitch();

    /**
     * \brief Checks if the control is a V-Pot assignment.
     * \return True if it's a V-Pot assignment, false otherwise.
     */
    bool isVpotAssignment();

    /**
     * \brief Checks if the control is part of the fader bank.
     * \return True if it's a faders bank control, false otherwise.
     */
    bool isFadersBank();

    /**
     * \brief Checks if the control corresponds to the display section.
     * \return True if it's a display control, false otherwise.
     */
    bool isDisplay();

    /**
     * \brief Checks if the control corresponds to function selection buttons.
     * \return True if it's a function selection control, false otherwise.
     */
    bool isFunctionSelection();

    /**
     * \brief Checks if the control is part of the global view section.
     * \return True if it's a global view control, false otherwise.
     */
    bool isGlobalView();

    /**
     * \brief Checks if the control is a modifier button (e.g., Shift, Alt).
     * \return True if it's a modifier control, false otherwise.
     */
    bool isModifier();

    /**
     * \brief Checks if the control is part of the automation section.
     * \return True if it's an automation control, false otherwise.
     */
    bool isAutomation();

    /**
     * \brief Checks if the control is part of the utilities section.
     * \return True if it's a utilities control, false otherwise.
     */
    bool isUtilities();

    /**
     * \brief Checks if the control falls into a miscellaneous category.
     * \return True if it's an uncategorized control, false otherwise.
     */
    bool isOther();

    /**
     * \brief Checks if the control is related to transport functions (e.g., play, stop).
     * \return True if it's a transport control, false otherwise.
     */
    bool isTranspot();

    /**
     * \brief Checks if the control is part of the navigation section (e.g., arrow buttons).
     * \return True if it's a navigation control, false otherwise.
     */
    bool isNavigation();

    /**
     * \brief Checks if the control is a user-defined switch.
     * \return True if it's a user switch, false otherwise.
     */
    bool isUserSwitch();

    /**
     * \brief Checks if a fader is currently being touched.
     * \return True if a fader is touched, false otherwise.
     */
    bool isFaderTouched();

    /**
     * \brief Checks if the control corresponds to a LED indicator.
     * \return True if it's a LED control, false otherwise.
     */
    bool isLed();

    /**
     * \brief Checks if the control triggers a relay click.
     * \return True if it's a relay click, false otherwise.
     */
    bool isRelayClick();

    /**
     * \brief Checks if the message is a fader position data.
     * \return True if it's a fader position control, false otherwise.
     */
    bool isFaderPosition();

    /**
     * \brief Getter for the control code
     * \return Enum of control code, CC_UNKNOWN if not known
     */
    cc_control_t getControl();

    /**
     * \brief Getter for a stringified version of this message
     * \return Const char containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents VpotRotation functions
 */
class MidiMcuVpotRotation : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuVpotRotation(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents ExternalControl functions
 */
class MidiMcuExternalControl : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuExternalControl(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents VpotLedRing functions
 */
class MidiMcuVpotLedRing : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuVpotLedRing(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents JogWheel functions
 */
class MidiMcuJogWheel : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuJogWheel(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents TimecodeDigit functions
 */
class MidiMcuTimecodeDigit : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuTimecodeDigit(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents AssignmentDigit functions
 */
class MidiMcuAssignmentDigit : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuAssignmentDigit(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Rec functions
 */
class MidiMcuRec : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuRec(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Solo functions
 */
class MidiMcuSolo : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuSolo(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Mute functions
 */
class MidiMcuMute : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuMute(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Select functions
 */
class MidiMcuSelect : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuSelect(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents VpotSwitch functions
 */
class MidiMcuVpotSwitch : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuVpotSwitch(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents VpotAssignment functions
 */
class MidiMcuVpotAssignment : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuVpotAssignment(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents FadersBank functions
 */
class MidiMcuFadersBank : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuFadersBank(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Display functions
 */
class MidiMcuDisplay : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuDisplay(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents FunctionSelection functions
 */
class MidiMcuFunctionSelection : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuFunctionSelection(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents GlobalView functions
 */
class MidiMcuGlobalView : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuGlobalView(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Modifier functions
 */
class MidiMcuModifier : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuModifier(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Automation functions
 */
class MidiMcuAutomation : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuAutomation(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Utilities functions
 */
class MidiMcuUtilities : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuUtilities(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Other functions
 */
class MidiMcuOther : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuOther(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Transpot functions
 */
class MidiMcuTranspot : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuTranspot(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Navigation functions
 */
class MidiMcuNavigation : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuNavigation(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents UserSwitch functions
 */
class MidiMcuUserSwitch : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuUserSwitch(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents FaderTouched functions
 */
class MidiMcuFaderTouched : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuFaderTouched(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents Led functions
 */
class MidiMcuLed : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuLed(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents RelayClick functions
 */
class MidiMcuRelayClick : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuRelayClick(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/
/**
 * \brief  Class that represents FaderPosition functions
 */
class MidiMcuFaderPosition : public MidiMCU {
   public:
    /**
     * \brief  Constructor
     * \param  message  MIDI massage
     */
    MidiMcuFaderPosition(midi::midi_msg_t message);

    /**
     * \brief  Getter for a stringified version of this message
     * \return  Const char* containing the string
     */
    const char* getString();
};

/**************************************************************************************************/

/**
 * \brief  Class that handles MIDI massages and control the protocol
 */
class MackieProtocol {
   public:
    /**
     * \brief Default constructor
     */
    MackieProtocol() = default;

    /**
     * \brief  Handle an arrived MIDI message
     */
    void handleMessage(MidiMCU message);

   protected:
    midixer::Track tracks_[MAX_MANAGED_TRACKS];  //!< Tracks being managed
    bool system_message_handling_;
    uint32_t system_messages_count_;
};

/**************************************************************************************************/

}  // namespace mcu

#endif  // __MIDIXER_SOFTWARE_INCLUDE_MACKIE_CONTROL_H__
