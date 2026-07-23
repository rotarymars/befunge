#include "code.hpp"
#include "gtest/gtest.h"
#include <sstream>

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

TEST(FungeSpace, LoadsGrid) {
  std::istringstream src(">123v\n    @\n");
  FungeSpace fs;
  fs.load(src);
  EXPECT_EQ(fs.get({0, 0}), '>');
  EXPECT_EQ(fs.get({4, 0}), 'v');
  EXPECT_EQ(fs.get({4, 1}), '@'); // second row: x resets after '\n'
  EXPECT_EQ(fs.get({1, 1}), 32);  // a space stays 32
}

TEST(FungeSpace, LoadStripsCarriageReturns) {
  std::istringstream src(">v\r\n@\r\n"); // Windows CRLF line endings
  FungeSpace fs;
  fs.load(src);
  EXPECT_EQ(fs.get({0, 0}), '>');
  EXPECT_EQ(fs.get({1, 0}), 'v');
  EXPECT_EQ(fs.get({2, 0}), 32);  // no stray '\r' stored at end of line
  EXPECT_EQ(fs.get({0, 1}), '@'); // next row starts at x=0, not shifted by '\r'
}

TEST(Vec, HashDistinguishesSwappedCoords) {
  EXPECT_NE((std::hash<Vec>{}({3, 5})), (std::hash<Vec>{}({5, 3})));
}