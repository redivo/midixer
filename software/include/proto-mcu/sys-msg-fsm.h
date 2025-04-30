/**************************************************************************************************/
/**
 * \file   sys-msg-fsm.h
 * \brief  Implementation of Mackie Control System Messages FSM
 *
 * This file was written based on information got through reverse engineering and by reding:
 *   https://github.com/NicoG60/TouchMCU/blob/main/doc/mackie_control_protocol.md
 */
/**************************************************************************************************/

#ifndef __MIDIXER_SOFTWARE_INCLUDE_PROTO_MCU_SYS_MSG_FSM_H__
#define __MIDIXER_SOFTWARE_INCLUDE_PROTO_MCU_SYS_MSG_FSM_H__

#include "proto-mcu/mackie-msg.h"

namespace mcu {

/**************************************************************************************************/
/**
 * \brief  Class that defines the Mackie Protocol System Message FSM
 */
class McuSystemMsgFsm {
   public:
    /**
     * \brief  Definition of all states of FSM
     */
    enum class State {
        Idle,
        Handle1st,
        Handle2nd,
        HandleLcd1st,
        HandleLcdOthers,
        HandleLcdLast,
        HandleNotImplemented,
    };

    /**
     * \brief Default constructor
     */
    McuSystemMsgFsm();

    /**
     * \brief  Handle an arrived MIDI message
     * \return TRUE if handled, FALSE if not handled
     */
    bool handle(MidiMcuMsg message);

    /**
     * \brief  Getter for track number
     */
    uint8_t getTrackNumber();

    /**
     * \brief  Getter for track name
     */
    const char* getTrackName();

    /**
     * \brief  Getter for curent state
     */
    McuSystemMsgFsm::State getState();

   protected:
    /**
     * \brief  Definition of commands
     */
    enum class Command {
        UpdateLCD = 0x12,
        Unknown = 0x7F,
    };

    /**
     * \brief  Go to the next state
     */
    void next();

    /**
     * \brief  Act according to the current state
     */
    void act();

    MidiMcuMsg last_message_;                   //!< Last received message to be handled
    State state_ = State::Idle;                 //!< Current state
    uint32_t manufacturer_id_ = 0;              //!< Last identified manufacturer ID
    uint8_t device_id_ = 0;                     //!< Last identified device ID
    Command command_id_ = Command::Unknown;     //!< Las identified command
    uint8_t track_num_ = 0;                     //!< Last identified track number
    char track_name_[MAX_TRACK_NAME_LCD_SIZE];  //!< Last identified track name
    uint8_t track_name_index_ = 0;              //!< Track name index, used internally
};

/**************************************************************************************************/

} // namespace mcu

#endif  // __MIDIXER_SOFTWARE_INCLUDE_PROTO_MCU_SYS_MSG_FSM_H__