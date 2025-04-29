/**************************************************************************************************/
/**
 * \file   midixer-cbs.h
 * \brief  Interface for MIdiXER callbacks
 *
 */
/**************************************************************************************************/

#ifndef __MIDIXER_SOFTWARE_INCLUDE_MIDIXER_MIDIXER_CB_INTF_H__
#define __MIDIXER_SOFTWARE_INCLUDE_MIDIXER_MIDIXER_CB_INTF_H__

namespace midixer {

/**
 * \brief  Interface class that defines the callbacks interface. Must be called by Protocol and
 *         implemented by Midixer
 */
class MidixerCbs {
   public:
    MidixerCbs() = default;

    /**
     * \brief  Update the name of a track
     * \param  track_num   Number of the track
     * \param  track_name  Name of the track to be updated
     */
    virtual void updateTrackName(uint8_t track_num, const char *track_name) = 0;

    /**
     * \brief  Update recording ARM state
     * \param  track_num   Number of the track
     * \param  arm         ARM state to be set
     */
    virtual void updateRecArm(uint8_t track_num, bool arm) = 0;

    /**
     * \brief  Update SOLO state
     * \param  track_num   Number of the track
     * \param  solo        Solo state to be set
     */
    virtual void updateSolo(uint8_t track_num, bool solo) = 0;

    /**
     * \brief  Update MUTE state
     * \param  track_num   Number of the track
     * \param  mute        Mute state to be set
     */
    virtual void updateMute(uint8_t track_num, bool mute) = 0;

    /**
     * \brief  Update fader position
     * \param  track_num   Number of the track
     * \param  pos         Fader position to be set
     */
    virtual void updateFaderPosition(uint8_t track_num, uint16_t pos) = 0;
};

} // namespace midixer

#endif  // __MIDIXER_SOFTWARE_INCLUDE_MIDIXER_MIDIXER_CB_INTF_H__