#include "MIDIUSB.h"

// Defines for System Real Time Messages
typedef enum {
    UNKNOWN = -1,
    NONE = 0x0,
    NOTE_OFF = 0x8,
    NOTE_ON = 0x9,
    POLYPHONIC_PRESSURE = 0xA,
    CONTROL_CHANGE = 0xB,
    PROGRAM_CHANGE = 0xC,
    CHANNEL_PRESSURE = 0xD,
    PITCH_BEND = 0xE,
    SYSTEM = 0xF,
} midi_msg_code_t;

/**************************************************************************************************/
/**
 * \brief Generic MIDI Event class
 */
class MidiMsg {
   public:

    /**********************************************************************************************/
    /**
     * \brief  Default constructor
     */
    MidiMsg() = default;

    /**********************************************************************************************/
    /**
     * \brief  Constructor given an event
     * \param  event  Event to be created
     */
    MidiMsg(midiEventPacket_t event) : raw_data_(event)
    {
    }

    /**********************************************************************************************/
    /**
     * \brief  Get string of code of MIDI message
     * \brief Return the string code of contained MIDI message
     */
    String getMidiMsgCodeStr()
    {
        if (raw_data_.header == 0) {
            return "NONE";
        }

        // The code is the first MS nybble of first byte
        uint8_t code = (raw_data_.byte1 & 0xF0) >> 4;

        // Search in codes
        switch (code) {
            case midi_msg_code_t::NOTE_OFF:
                return "NOTE_OFF";

            case midi_msg_code_t::NOTE_ON:
                return "NOTE_ON";

            case midi_msg_code_t::POLYPHONIC_PRESSURE:
                return "POLYPHONIC_PRESSURE";

            case midi_msg_code_t::CONTROL_CHANGE:
                return "CONTROL_CHANGE";

            case midi_msg_code_t::PROGRAM_CHANGE:
                return "PROGRAM_CHANGE";

            case midi_msg_code_t::CHANNEL_PRESSURE:
                return "CHANNEL_PRESSURE";

            case midi_msg_code_t::PITCH_BEND:
                return "PITCH_BEND";

            case midi_msg_code_t::SYSTEM:
                return "SYSTEM";

            default:
                return "UNKNOWN: " + String(raw_data_.header);
        }
    }


    uint8_t getRawMsgCode()
    {
        // MIDI Message code is in MS nybble of byte 1
        return (raw_data_.byte1 & 0xF0) >> 4;
    }

    uint8_t getRawMidiChannel()
    {
        // MIDI Channel is inLS nybble of byte 1
        return (raw_data_.byte1 & 0x0F);
    }

    uint8_t getRawNote()
    {
        // Note is the 7 LSB of byte 2
        return raw_data_.byte2 & 0x3F;
    }

    uint8_t getRawVelocity()
    {
        // Note is the 7 LSB of byte 3
        return raw_data_.byte3 & 0x3F;
    }

    /**********************************************************************************************/
    /**
     * \brief  Get code of MIDI message
     * \brief Return the code of contained MIDI message
     */
    midi_msg_code_t getMidiMsgCode()
    {
        if (raw_data_.header == 0) {
            return midi_msg_code_t::NONE;
        }

        // Search in codes
        switch (getRawMsgCode()) {
            case midi_msg_code_t::NOTE_OFF:
                return midi_msg_code_t::NOTE_OFF;

            case midi_msg_code_t::NOTE_ON:
                return midi_msg_code_t::NOTE_ON;

            case midi_msg_code_t::POLYPHONIC_PRESSURE:
                return midi_msg_code_t::POLYPHONIC_PRESSURE;

            case midi_msg_code_t::CONTROL_CHANGE:
                return midi_msg_code_t::CONTROL_CHANGE;

            case midi_msg_code_t::PROGRAM_CHANGE:
                return midi_msg_code_t::PROGRAM_CHANGE;

            case midi_msg_code_t::CHANNEL_PRESSURE:
                return midi_msg_code_t::CHANNEL_PRESSURE;

            case midi_msg_code_t::PITCH_BEND:
                return midi_msg_code_t::PITCH_BEND;

            case midi_msg_code_t::SYSTEM:
                return midi_msg_code_t::SYSTEM;

            default:
                return midi_msg_code_t::UNKNOWN;
        }
    }

    /**********************************************************************************************/
    /**
     * \brief  Get string of raw data
     */
    String getRawDataString()
    {
        char buff[64];
        sprintf(buff, "Header: 0x%02x\r\n"
                      "Byte 1: 0x%02x\r\n"
                      "Byte 2: 0x%02x\r\n"
                      "Byte 3: 0x%02x\r\n", raw_data_.header,
                                            raw_data_.byte1,
                                            raw_data_.byte2,
                                            raw_data_.byte3);

        return String(buff);
    }

    int getControl()
    {
        if (getMidiMsgCode() != midi_msg_code_t::CONTROL_CHANGE) {
            return -1;
        }

        return raw_data_.byte2;
    }

    String getString()
    {
        String s;
        s = String("==============================\r\n");
        s += getMidiMsgCodeStr() + String("\r\n");
        s += getRawDataString() + String("\r\n");

        return s;
    }

    /**********************************************************************************************/

    midiEventPacket_t raw_data_;
};

/**************************************************************************************************/
class MidiMcuVpotRotation();
//class MidiMcuExternalControl()
//class MidiMcuVpotLedRing()
//class MidiMcuJogWheel()
//class MidiMcuTimecodeDigit()
//class MidiMcuAssignmentDigit()
//class MidiMcuRec()
//class MidiMcuSolo()
//class MidiMcuMute()
//class MidiMcuSelect()
//class MidiMcuVpotSwitch()
//class MidiMcuVpotAssignment()
//class MidiMcuFadersBank()
//class MidiMcuDisplay()
//class MidiMcuFunctionSelection()
//class MidiMcuGlobalView()
//class MidiMcuModifier()
//class MidiMcuAutomation()
//class MidiMcuUtilities()
//class MidiMcuOther()
//class MidiMcuTranspot()
//class MidiMcuNavigation()
//class MidiMcuUserSwitch()
//class MidiMcuFaderTouched()
//class MidiMcuLed()
//class MidiMcuRelayClick()
//class MidiMcuFaderPosition()

class MidiMCU : public MidiMsg {

   public:

    // Defines for Control Change Controls
    typedef enum {
        UNKNOWN_CONTROL = -1,

        VPOT_1_ROTATION = 0x10, // Valid for MIDI channel 0
        VPOT_2_ROTATION = 0x11, // Valid for MIDI channel 0
        VPOT_3_ROTATION = 0x12, // Valid for MIDI channel 0
        VPOT_4_ROTATION = 0x13, // Valid for MIDI channel 0
        VPOT_5_ROTATION = 0x14, // Valid for MIDI channel 0
        VPOT_6_ROTATION = 0x18, // Valid for MIDI channel 0
        VPOT_7_ROTATION = 0x16, // Valid for MIDI channel 0
        VPOT_8_ROTATION = 0x17, // Valid for MIDI channel 0

        EXTERNAL_CONTROL = 0x2E, // Valid for MIDI channel 0

        VPOT_1_LED_RING = 0x30, // Valid for MIDI channel 0
        VPOT_2_LED_RING = 0x31, // Valid for MIDI channel 0
        VPOT_3_LED_RING = 0x32, // Valid for MIDI channel 0
        VPOT_4_LED_RING = 0x33, // Valid for MIDI channel 0
        VPOT_5_LED_RING = 0x34, // Valid for MIDI channel 0
        VPOT_6_LED_RING = 0x35, // Valid for MIDI channel 0
        VPOT_7_LED_RING = 0x36, // Valid for MIDI channel 0
        VPOT_8_LED_RING = 0x37, // Valid for MIDI channel 0

        JOG_WHEEL = 0x3C, // Valid for MIDI channel 0

        TIMECODE_DIGIT_1 = 0x40, // Valid for MIDI channel 0 or 15
        TIMECODE_DIGIT_2 = 0x41, // Valid for MIDI channel 0 or 15
        TIMECODE_DIGIT_3 = 0x42, // Valid for MIDI channel 0 or 15
        TIMECODE_DIGIT_4 = 0x43, // Valid for MIDI channel 0 or 15
        TIMECODE_DIGIT_5 = 0x44, // Valid for MIDI channel 0 or 15
        TIMECODE_DIGIT_6 = 0x45, // Valid for MIDI channel 0 or 15
        TIMECODE_DIGIT_7 = 0x46, // Valid for MIDI channel 0 or 15
        TIMECODE_DIGIT_8 = 0x47, // Valid for MIDI channel 0 or 15
        TIMECODE_DIGIT_9 = 0x48, // Valid for MIDI channel 0 or 15
        TIMECODE_DIGIT_10 = 0x49, // Valid for MIDI channel 0 or 15

        ASSIGNMENT_DIGIT_1 = 0x4A, // Valid for MIDI channel 0 or 15
        ASSIGNMENT_DIGIT_2 = 0x4B, // Valid for MIDI channel 0 or 15

    } cc_control_t;

    // Defines note mapping, valid for MIDI channel 0
    typedef enum {
        UNKNOWN_NOTE = -1,

        REC_1 = 0x00,
        REC_2 = 0x01,
        REC_3 = 0x02,
        REC_4 = 0x03,
        REC_5 = 0x04,
        REC_6 = 0x05,
        REC_7 = 0x06,
        REC_8 = 0x07,

        SOLO_1 = 0x08,
        SOLO_2 = 0x09,
        SOLO_3 = 0x0A,
        SOLO_4 = 0x0B,
        SOLO_5 = 0x0C,
        SOLO_6 = 0x0D,
        SOLO_7 = 0x0E,
        SOLO_8 = 0x0F,

        MUTE_1 = 0x10,
        MUTE_2 = 0x11,
        MUTE_3 = 0x12,
        MUTE_4 = 0x13,
        MUTE_5 = 0x14,
        MUTE_6 = 0x15,
        MUTE_7 = 0x16,
        MUTE_8 = 0x17,

        SELECT_1 = 0x18,
        SELECT_2 = 0x19,
        SELECT_3 = 0x1A,
        SELECT_4 = 0x1B,
        SELECT_5 = 0x1C,
        SELECT_6 = 0x1D,
        SELECT_7 = 0x1E,
        SELECT_8 = 0x1F,

        VPOT_SWITCH_1 = 0x20,
        VPOT_SWITCH_2 = 0x21,
        VPOT_SWITCH_3 = 0x22,
        VPOT_SWITCH_4 = 0x23,
        VPOT_SWITCH_5 = 0x24,
        VPOT_SWITCH_6 = 0x25,
        VPOT_SWITCH_7 = 0x26,
        VPOT_SWITCH_8 = 0x27,

        ASSIGN_TRACK = 0x28,
        ASSIGN_SEND = 0x29,
        ASSIGN_PAN = 0x2A,
        ASSIGN_PLUGIN = 0x2B,
        ASSIGN_EQ = 0x2C,
        ASSIGN_INSTRUMENT = 0x2D,

        BANK_LEFT = 0x2E,
        BANK_RIGHT = 0x2F,
        CHANNEL_LEFT = 0x30,
        CHANNEL_RIGHT = 0x31,
        FLIP = 0x32,
        GLOBAL = 0x33,

        NAME_VAL_BUTTON = 0x34,
        SMPTE_BEATS_BUTTON = 0x35,

        F1 = 0x36,
        F2 = 0x37,
        F3 = 0x38,
        F4 = 0x39,
        F5 = 0x3A,
        F6 = 0x3B,
        F7 = 0x3C,
        F8 = 0x3D,

        MIDI_TRACKS = 0x3E,
        INPUTS = 0x3F,
        AUDIO_TRACKS = 0x40,
        AUDIO_INTRUMENTS = 0x41,
        AUX = 0x42,
        BUSSES = 0x43,
        OUTPUTS = 0x44,
        USER = 0x45,

        SHIFT = 0x46,
        OPTION = 0x47,
        CONTROL = 0x48,
        ALT = 0x49,

        READ_OFF = 0x4A,
        WRITE = 0x4B,
        TRIM = 0x4C,
        TOUCH = 0x4D,
        LATCH = 0x4E,
        GROUP = 0x4F,

        SAVE = 0x50,
        UNDO = 0x51,
        CANCEL = 0x52,
        ENTER = 0x53,

        MARKERS = 0x54,
        NUDGE = 0x55,
        CYCLE = 0x56,
        DROP = 0x57,
        REPLACE = 0x58,
        CLICK = 0x59,
        SOLO = 0x5A,

        REWIND = 0x5B,
        FORWARD = 0x5C,
        STOP = 0x5D,
        PLAY = 0x5E,
        RECORD = 0x5F,

        UP = 0x60,
        DOWN = 0x61,
        LEFT = 0x62,
        RIGHT = 0x63,
        ZOOM = 0x64,
        SCRUB = 0x65,

        USER_SWITCH_1 = 0x66,
        USER_SWITCH_2 = 0x67,

        FADER_1_TOUCHED = 0x68,
        FADER_2_TOUCHED = 0x69,
        FADER_3_TOUCHED = 0x6A,
        FADER_4_TOUCHED = 0x6B,
        FADER_5_TOUCHED = 0x6C,
        FADER_6_TOUCHED = 0x6D,
        FADER_7_TOUCHED = 0x6E,
        FADER_8_TOUCHED = 0x6F,
        MASTER_FADER_TOUCHED = 0x70,

        SMPTE_LED = 0x71,
        BEATS_LED = 0x72,
        RUDE_SOLO_LED = 0x73,

        RELAY_CLICK = 0x76,

    } notes_t;

    /**********************************************************************************************/
    /**
     * \brief  Constructor given an event
     * \param  event  Event to be created
     */
    MidiMCU(midiEventPacket_t event) : MidiMsg(event)
    {
    }

    bool isVpotRotation()
    {
        return (getMidiMsgCode() == CONTROL_CHANGE &&
                getRawMidiChannel() == 0 &&
                getControl() >= VPOT_1_ROTATION &&
                getControl() <= VPOT_8_ROTATION);
    }

    bool isExternalControl()
    {
        return (getMidiMsgCode() == CONTROL_CHANGE &&
                getRawMidiChannel() == 0 &&
                getControl() == EXTERNAL_CONTROL);
    }

    bool isVpotLedRing()
    {
        return (getMidiMsgCode() == CONTROL_CHANGE &&
                getRawMidiChannel() == 0 &&
                getControl() >= VPOT_1_LED_RING &&
                getControl() <= VPOT_8_LED_RING);
    }

    bool isJogWheel()
    {
        return (getMidiMsgCode() == CONTROL_CHANGE &&
                getRawMidiChannel() == 0 &&
                getControl() == JOG_WHEEL);
    }

    bool isTimecodeDigit()
    {
        return (getMidiMsgCode() == CONTROL_CHANGE &&
                (getRawMidiChannel() == 0 || getRawMidiChannel() == 15) &&
                getControl() >= TIMECODE_DIGIT_1 &&
                getControl() <= TIMECODE_DIGIT_10);
    }

    bool isAssignmentDigit()
    {
        return (getMidiMsgCode() == CONTROL_CHANGE &&
                (getRawMidiChannel() == 0 || getRawMidiChannel() == 15) &&
                getControl() >= ASSIGNMENT_DIGIT_1 &&
                getControl() <= ASSIGNMENT_DIGIT_2);
    }

    bool isRec()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= REC_1 &&
                getRawNote() <= REC_8);
    }

    bool isSolo()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= SOLO_1 &&
                getRawNote() <= SOLO_8);
    }

    bool isMute()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= MUTE_1 &&
                getRawNote() <= MUTE_8);
    }

    bool isSelect()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= SELECT_1 &&
                getRawNote() <= SELECT_8);
    }

    bool isVpotSwitch()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= VPOT_SWITCH_1 &&
                getRawNote() <= VPOT_SWITCH_8);
    }

    bool isVpotAssignment()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= ASSIGN_TRACK &&
                getRawNote() <= ASSIGN_INSTRUMENT);
    }

    bool isFadersBank()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= BANK_LEFT &&
                getRawNote() <= GLOBAL);
    }

    bool isDisplay()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= NAME_VAL_BUTTON &&
                getRawNote() <= SMPTE_BEATS_BUTTON);
    }

    bool isFunctionSelection()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= F1 &&
                getRawNote() <= F8);
    }

    bool isGlobalView()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= MIDI_TRACKS &&
                getRawNote() <= USER);
    }

    bool isModifier()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= SHIFT &&
                getRawNote() <= ALT);
    }

    bool isAutomation()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= READ_OFF &&
                getRawNote() <= GROUP);
    }

    bool isUtilities()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= SAVE &&
                getRawNote() <= ENTER);
    }

    bool isOther()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= MARKERS &&
                getRawNote() <= SOLO);
    }

    bool isTranspot()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= REWIND &&
                getRawNote() <= RECORD);
    }

    bool isNavigation()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= UP &&
                getRawNote() <= SCRUB);
    }

    bool isUserSwitch()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= USER_SWITCH_1 &&
                getRawNote() <= USER_SWITCH_2);
    }

    bool isFaderTouched()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= FADER_1_TOUCHED &&
                getRawNote() <= MASTER_FADER_TOUCHED);
    }

    bool isLed()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() >= SMPTE_LED &&
                getRawNote() <= RUDE_SOLO_LED);
    }

    bool isRelayClick()
    {
        return (getMidiMsgCode() == NOTE_ON &&
                getRawMidiChannel() == 0 &&
                getRawNote() == RELAY_CLICK);
    }

    bool isFaderPosition()
    {
        return (getMidiMsgCode() == PITCH_BEND);
    }


    cc_control_t getControl() {
        int control = MidiMsg::getControl();

        // TODO verificar canal
        switch (control) {
            case VPOT_1_ROTATION:
            case VPOT_2_ROTATION:
            case VPOT_3_ROTATION:
            case VPOT_4_ROTATION:
            case VPOT_5_ROTATION:
            case VPOT_6_ROTATION:
            case VPOT_7_ROTATION:
            case VPOT_8_ROTATION:
            case EXTERNAL_CONTROL:
            case VPOT_1_LED_RING:
            case VPOT_2_LED_RING:
            case VPOT_3_LED_RING:
            case VPOT_4_LED_RING:
            case VPOT_5_LED_RING:
            case VPOT_6_LED_RING:
            case VPOT_7_LED_RING:
            case VPOT_8_LED_RING:
            case JOG_WHEEL:
            case TIMECODE_DIGIT_1:
            case TIMECODE_DIGIT_2:
            case TIMECODE_DIGIT_3:
            case TIMECODE_DIGIT_4:
            case TIMECODE_DIGIT_5:
            case TIMECODE_DIGIT_6:
            case TIMECODE_DIGIT_7:
            case TIMECODE_DIGIT_8:
            case TIMECODE_DIGIT_9:
            case TIMECODE_DIGIT_10:
            case ASSIGNMENT_DIGIT_1:
            case ASSIGNMENT_DIGIT_2:
                return static_cast<cc_control_t>(control);

            default:
                return UNKNOWN_CONTROL;
        }
    }

    char getTimecodeChar() {
        return static_cast<char>(raw_data_.byte3);
    }

    String getString(bool printKnown = true)
    {
        String s;

        if (isVpotRotation()) {
            // It is a known command. Only print if requested
            if (printKnown) {
                s = String("==============================\r\n");
                s += "VPOT_ROTATION: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isExternalControl()) {
            // It is a known command. Only print if requested
            if (printKnown) {
                s = String("==============================\r\n");
                s += "EXTERNAL_CONTROL: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isVpotLedRing()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "VPOT_LED_RING: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isJogWheel()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "JOG_WHEEL: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isTimecodeDigit()) {
            // It is a known command. Only print if requested
            //if (printKnown) {
            //    s = String("==============================\r\n");
            //    s += "TIMECODE " + String(getControl() & 0x0F) + ": " + getTimecodeChar()
            //       + " (ch " + String(getRawMidiChannel()) + ")" + String("\r\n");
            //}
        }

        else if (isAssignmentDigit()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "ASSIGNMENT_DIGIT: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isRec()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "REC: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isSolo()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "SOLO: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isMute()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "MUTE: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isSelect()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "SELECT: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isVpotSwitch()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "VPOT_SWITCH: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isVpotAssignment()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "ASSIGNMENT: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isFadersBank()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "FADER_BANK: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isDisplay()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "DISPLAY: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isFunctionSelection()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "FUNCTION: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isGlobalView()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "GLOBAL_VIEW: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isModifier()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "MODIFIER: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isAutomation()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "AUTOMATION: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isUtilities()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "UTILS: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isOther()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "OTHER: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isTranspot()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "TRANSPOT: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isNavigation()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "NAVIGATION: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isUserSwitch()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "USER_SWITCH: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isFaderTouched()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "FADER_TOUCHED: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isLed()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "LED: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isRelayClick()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "CLICK: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else if (isFaderPosition()) {
            if (printKnown) {
                s = String("==============================\r\n");
                s += "FADER_POSITION: " + String(raw_data_.byte2) + ", " + String(raw_data_.byte3) + String("\r\n");
            }
        }

        else {
            s = MidiMsg::getString();
        }

        return s;
    }

    String getStringUnknownOnly()
    {
        return getString(false);
    }
};
