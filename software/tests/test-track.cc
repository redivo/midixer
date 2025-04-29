/**************************************************************************************************/
/**
 * \file   test-track.cc
 * \brief  Tests for MidiMsg class
 */
/**************************************************************************************************/

#include <gtest/gtest.h>
#include "midixer/track.h"

using namespace midixer;

/**************************************************************************************************/

TEST(TrackTest, DefaultMuteIsFalse) {
    Track track;

    EXPECT_FALSE(track.getMute());
}

/**************************************************************************************************/

TEST(TrackTest, SetAndGetMute) {
    Track track;

    track.setMute(true);
    EXPECT_TRUE(track.getMute());

    track.setMute(false);
    EXPECT_FALSE(track.getMute());
}

/**************************************************************************************************/

TEST(TrackTest, DefaultSoloIsFalse) {
    Track track;

    EXPECT_FALSE(track.getSolo());
}

/**************************************************************************************************/

TEST(TrackTest, SetAndGetSolo) {
    Track track;

    track.setSolo(true);
    EXPECT_TRUE(track.getSolo());

    track.setSolo(false);
    EXPECT_FALSE(track.getSolo());
}

/**************************************************************************************************/

TEST(TrackTest, DefaultArmIsFalse) {
    Track track;

    EXPECT_FALSE(track.getArm());
}

/**************************************************************************************************/

TEST(TrackTest, SetAndGetArm) {
    Track track;

    track.setArm(true);
    EXPECT_TRUE(track.getArm());

    track.setArm(false);
    EXPECT_FALSE(track.getArm());
}

/**************************************************************************************************/

TEST(TrackTest, DefaultNumberIsZero) {
    Track track;

    EXPECT_EQ(track.getNumber(), 0);
}

/**************************************************************************************************/

TEST(TrackTest, SetAndGetNumber) {
    Track track;

    track.setNumber(5);
    EXPECT_EQ(track.getNumber(), 5);
}

/**************************************************************************************************/

TEST(TrackTest, DefaultFaderIsZero) {
    Track track;

    EXPECT_EQ(track.getFader(), 0);
}

/**************************************************************************************************/

TEST(TrackTest, SetAndGetFader) {
    Track track;

    track.setFader(127);
    EXPECT_EQ(track.getFader(), 127);
}

/**************************************************************************************************/

TEST(TrackTest, DefaultPanIsZero) {
    Track track;

    EXPECT_EQ(track.getPan(), 0);
}

/**************************************************************************************************/

TEST(TrackTest, SetAndGetPan) {
    Track track;

    track.setPan(-50);
    EXPECT_EQ(track.getPan(), -50);

    track.setPan(50);
    EXPECT_EQ(track.getPan(), 50);

    track.setPan(0);
    EXPECT_EQ(track.getPan(), 0);
    
    track.setPan(101);
    EXPECT_EQ(track.getPan(), 100);

    track.setPan(-100);
    EXPECT_EQ(track.getPan(), -100);

    track.setPan(100);
    EXPECT_EQ(track.getPan(), 100);

    track.setPan(-101);
    EXPECT_EQ(track.getPan(), -100);
}

/**************************************************************************************************/

TEST(TrackTest, DefaultMeterIsZero) {
    Track track;

    EXPECT_EQ(track.getMeter(), 0);
}

/**************************************************************************************************/

TEST(TrackTest, SetAndGetMeter) {
    Track track;

    track.setMeter(80);
    EXPECT_EQ(track.getMeter(), 80);
}

/**************************************************************************************************/

TEST(TrackTest, DefaultNameIsEmpty) {
    Track track;

    const char* name = track.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "");
}

/**************************************************************************************************/

TEST(TrackTest, SetAndGetName) {
    Track track;

    char testName[MAX_TRACK_NAME_LEN] = "Guitar Track";
    track.setName(testName);
    EXPECT_STREQ(track.getName(), testName);
}