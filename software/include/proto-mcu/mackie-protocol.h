/**************************************************************************************************/
/**
 * \file   mackie-protocol.h
 * \brief  Implementation of Mackie Control Protocol
 *
 * This file was written based on information got through reverse engineering and by reding:
 *   https://github.com/NicoG60/TouchMCU/blob/main/doc/mackie_control_protocol.md
 */
/**************************************************************************************************/

#ifndef __MIDIXER_SOFTWARE_INCLUDE_PROTO_MCU_MACKIE_PROTOCOL_H__
#define __MIDIXER_SOFTWARE_INCLUDE_PROTO_MCU_MACKIE_PROTOCOL_H__

#include "proto-mcu/sys-msg-fsm.h"
#include "midixer/midixer-cb-intf.h"

namespace mcu {

/**************************************************************************************************/
/**
 * \brief  Class that handles MIDI massages and control the protocol
 */
class MackieProtocol {
   public:
    /**
     * \brief Default constructor
     */
    MackieProtocol(midixer::MidixerCbs *midixer);

    /**
     * \brief  Handle an arrived MIDI message
     */
    void handleMessage(MidiMcuMsg message);

   protected:
    McuSystemMsgFsm system_msg_fsm_;  //!< System Message FSM
    midixer::MidixerCbs *midixer_;    //!< Callback to call MIdiXER
};

/**************************************************************************************************/

}  // namespace mcu

#endif  // __MIDIXER_SOFTWARE_INCLUDE_PROTO_MCU_MACKIE_PROTOCOL_H__