/**************************************************************************************************/
/**
 * \file   midi-msg.h
 * \brief  Implementation of generic MIDI messages
 *
 * This file was written based on information of these two references:
 *   https://learn.sparkfun.com/tutorials/midi-tutorial/
 *   https://midi.org/summary-of-midi-1-0-messages
 */
/**************************************************************************************************/

#ifndef __MIDIXER_SOFTWARE_INCLUDE_MIDI_MSG_H__
#define __MIDIXER_SOFTWARE_INCLUDE_MIDI_MSG_H__

#include <stdint.h>

//!< Maximum size of a raw data string used in this class
#define MIDI_MSG_MAX_RAW_DATA_STRING_SIZE 64

//!< Maximum size of a message type name string used in this class
#define MIDI_MSG_MAX_TYPE_STRING_SIZE 32

//!< Maximum size of a string used in this class
#define MIDI_MSG_MAX_STRING_SIZE (MIDI_MSG_MAX_RAW_DATA_STRING_SIZE + MIDI_MSG_MAX_TYPE_STRING_SIZE)


/**************************************************************************************************/
/**
 * \brief  Struct that defines a generic MIDI raw data
 */
typedef struct {
    uint8_t byte1;  //!< Here we have message type in MS Nyble and MIDI channel in LS Nyble
    uint8_t byte2;  //!< This data depends on the first one
    uint8_t byte3;  //!< This data depends on the first and second ones
} midi_msg_t;

/**************************************************************************************************/
/**
 * \brief  Enum that defines known MIDI message types
 */
typedef enum {
    MSG_TYPE_UNKNOWN = -1,
    MSG_TYPE_NONE = 0x0,
    MSG_TYPE_NOTE_OFF = 0x8,
    MSG_TYPE_NOTE_ON = 0x9,
    MSG_TYPE_POLYPHONIC_PRESSURE = 0xA,
    MSG_TYPE_CONTROL_CHANGE = 0xB,
    MSG_TYPE_PROGRAM_CHANGE = 0xC,
    MSG_TYPE_CHANNEL_PRESSURE = 0xD,
    MSG_TYPE_PITCH_BEND = 0xE,
    MSG_TYPE_SYSTEM = 0xF,
} midi_msg_type_t;

/**************************************************************************************************/
/**
 * \brief  Class that defines a generic MIDI raw data
 */
class MidiMsg {
   public:
    /**
     * \brief  Default Constructor
     */
    MidiMsg() = default;

    /**
     * \brief  Constructor
     * \param  midi  Midi data to be used
     */
    MidiMsg(midi_msg_t midi);

    /**********************************************************************************************/
    /* Getters                                                                                    */
    /**********************************************************************************************/

    /**
     * \brief  Getter for message type.
     * \return The enum of message type, MSG_TYPE_NONE if zeroed or MSG_TYPE_UNKNOWN if unknown.
     */
    midi_msg_type_t getMsgType();

    /**
     * \brief  Getter for control of MSG_TYPE_CONTROL_CHANGE messages.
     * \return The integer value of control if it is a MSG_TYPE_CONTROL_CHANGE, -1 otherwise.
     */
    int8_t getControl();

    /**
     * \brief  Getter for a stringified version of message.
     * \return A string representation of MIDI message.
     */
    const char* getString();

    /**
     * \brief  Getter for a stringified version of message type.
     * \return A string representation of MIDI message type.
     */
    const char* getMsgTypeStr();

    /**********************************************************************************************/
    /* Raw Getters                                                                                */
    /*                                                                                            */
    /* Here are the getters without any verification. You have to be sure about the midi type     */
    /* to use it.                                                                                 */
    /*                                                                                            */
    /* For example, if you call getRawNote() for a MSG_TYPE_PITCH_BEND message it will return a   */
    /* value the is not a note. Be careful.                                                       */
    /**********************************************************************************************/

    /**
     * \brief  Getter for a stringified version of message without any validations. Just values.
     * \return A string representation of raw MIDI message.
     */
    const char* getRawDataString();

    /**
     * \brief  Getter for raw message type. Does not perform any verification in data.
     * \return Message type
     */
    uint8_t getRawMsgType();

    /**
     * \brief  Getter for raw MIDI channel. Does not perform any verification in data and assumes
     *         that the message has a MIDI channel in it.
     * \return MIDI channel
     */
    uint8_t getRawMidiChannel();

    /**
     * \brief  Getter for raw note. Does not perform any verification in data and assumes that the
     *         message has a MIDI note in it.
     * \return Note
     */
    uint8_t getRawNote();

    /**
     * \brief  Getter for raw velocity. Does not perform any verification in data and assumes that
     *         the message has a MIDI velocity in it.
     * \return Velocity
     */
    uint8_t getRawVelocity();

   protected:
    midi_msg_t raw_data_;  //!< Raw MIDI data
};

#endif // __MIDIXER_SOFTWARE_INCLUDE_MIDI_MSG_H__
