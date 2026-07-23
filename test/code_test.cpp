#include "code.hpp"
#include "gtest/gtest.h"

TEST(FungeSpace, NegativeCoordinatesRoundTrip) {
    FungeSpace fs;
    fs.put({-1, -1}, 'X');
    EXPECT_EQ(fs.get({-1, -1}), 'X');
}

TEST(FungeSpace, UntouchedCellsAreSpace) {
    FungeSpace fs;
    EXPECT_EQ(fs.get({100, 100}), 32);
}

TEST(FungeSpace, SameChunkCellsCoexist) {
    FungeSpace fs;
    fs.put({0, 0}, 'A');
    fs.put({4, 1}, 'B');
    EXPECT_EQ(fs.get({0, 0}), 'A');
    EXPECT_EQ(fs.get({4, 1}), 'B');
}

TEST(FungeSpace, BoundsTrackUsedRegion) {
    FungeSpace fs;
    fs.put({-1, -1}, 'X');
    fs.put({4, 1}, 'B');
    EXPECT_EQ(fs.min().x, -1);
    EXPECT_EQ(fs.max().x, 4);
}

TEST(Vec, HashDistinguishesSwappedCoords) {
    EXPECT_NE((std::hash<Vec>{}({3, 5})), (std::hash<Vec>{}({5, 3})));
}