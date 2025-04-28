/**************************************************************************************************/
/**
 * \file   track.h
 * \brief  Representation of a track in a DAW
 */
/**************************************************************************************************/

#ifndef __MIDIXER_SOFTWARE_INCLUDE_TRACK_H__
#define __MIDIXER_SOFTWARE_INCLUDE_TRACK_H__

#include <stdint.h>

//!< Max size of a track name
#define MAX_TRACK_NAME_LEN 24

namespace midixer {

/**************************************************************************************************/

/**
 * \brief  Class that represents a track of a DAW
 */
class Track {
   public:
    /**
     * \brief  Constructor
     */
    Track() = default;

    /**
     * \brief  Getter for mute
     * \return Mute state
     */
    bool getMute();

    /**
     * \brief  Setter for mute
     * \param  mute  Value to be set
     */
    void setMute(bool mute);

    /**
     * \brief  Getter for solo
     * \return Solo state
     */
    bool getSolo();

    /**
     * \brief  Setter for solo
     * \param  solo  Value to be set
     */
    void setSolo(bool solo);

    /**
     * \brief  Getter for arm
     * \return Arm state
     */
    bool getArm();

    /**
     * \brief  Setter for arm
     * \param  arm  Value to be set
     */
    void setArm(bool arm);

    /**
     * \brief  Getter for number
     * \return Number state
     */
    uint8_t getNumber();

    /**
     * \brief  Setter for number
     * \param  number  Value to be set
     */
    void setNumber(uint8_t number);

    /**
     * \brief  Getter for fader
     * \return Fader state
     */
    uint8_t getFader();

    /**
     * \brief  Setter for fader
     * \param  fader  Value to be set
     */
    void setFader(uint8_t fader);

    /**
     * \brief  Getter for pan
     * \return Pan state, where -100 means 100%L and 100 means 100%R
     */
    int8_t getPan();

    /**
     * \brief  Setter for pan
     * \param  pan  Value to be set, where -100 means 100%L and 100 means 100%R. If you set a value
     *              greater than (+/-)100, the pan will assume (+/-)100.
     */
    void setPan(int8_t pan);

    /**
     * \brief  Getter for meter
     * \return Meter state
     */
    uint8_t getMeter();

    /**
     * \brief  Setter for meter
     * \param  meter  Value to be set
     */
    void setMeter(uint8_t meter);

    /**
     * \brief  Getter for name
     * \return Name state
     */
    const char* getName();

    /**
     * \brief  Setter for name
     * \param  name  Value to be set
     */
    void setName(char name[MAX_TRACK_NAME_LEN]);

   protected:
    bool mute_state_ = false;        //!< Mute ON/OFF
    bool solo_state_ = false;        //!< Solo ON/OFF
    bool arm_state_ = false;         //!< Arm record ON/OFF
    uint8_t number_ = 0;             //!< Track number
    uint8_t fader_level_ = 0;        //!< Fader volume level
    int8_t pan_ = 0;                 //!< Pan configuration
    uint8_t meter_ = 0;              //!< Volume Meter
    char name_[MAX_TRACK_NAME_LEN];  //!< Track Name
};

/**************************************************************************************************/

}  // namespace midixer

#endif  // __MIDIXER_SOFTWARE_INCLUDE_TRACK_H__
