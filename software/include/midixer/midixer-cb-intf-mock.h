/**************************************************************************************************/
/**
 * \file   midixer-cbs-intf-mock.h
 * \brief  Interface for MIdiXER callbacks
 *
 */
/**************************************************************************************************/

#ifndef __MIDIXER_SOFTWARE_INCLUDE_MIDIXER_MIDIXER_CB_INTF_MOCK_H__
#define __MIDIXER_SOFTWARE_INCLUDE_MIDIXER_MIDIXER_CB_INTF_MOCK_H__

#include <gmock/gmock.h>
#include "midixer/midixer-cb-intf.h"

namespace midixer {

/**
 * \brief  Mock for MidixerCbs class
 */
class MockMidixerCbs : public MidixerCbs {
   public:
    MOCK_METHOD(void, updateTrackName, (uint8_t, const char *));
    MOCK_METHOD(void, updateRecArm, (uint8_t, bool));
    MOCK_METHOD(void, updateSolo, (uint8_t, bool));
    MOCK_METHOD(void, updateMute, (uint8_t, bool));
    MOCK_METHOD(void, updateFaderPosition, (uint8_t, uint16_t));
};

} // namespace midixer

#endif  // __MIDIXER_SOFTWARE_INCLUDE_MIDIXER_MIDIXER_CB_INTF_MOCK_H__