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

TEST(Stack, NewStackIsEmpty) {
  Stack s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

TEST(Stack, PopEmptyReturnsZero) {
  Stack s;
  EXPECT_EQ(s.pop(), 0); // the critical Befunge rule: underflow yields 0
  EXPECT_EQ(s.pop(), 0); // still 0, still safe
  EXPECT_TRUE(s.empty());
}

TEST(Stack, PeekEmptyReturnsZero) {
  Stack s;
  EXPECT_EQ(s.peek(), 0);
  EXPECT_TRUE(s.empty()); // peek must not consume anything
}

TEST(Stack, PushPopIsLifo) {
  Stack s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.pop(), 3);
  EXPECT_EQ(s.pop(), 2);
  EXPECT_EQ(s.pop(), 1);
  EXPECT_EQ(s.pop(), 0); // drained past empty -> 0
}

TEST(Stack, PeekDoesNotConsume) {
  Stack s;
  s.push(42);
  EXPECT_EQ(s.peek(), 42);
  EXPECT_EQ(s.peek(), 42); // still there
  EXPECT_EQ(s.size(), 1u);
  EXPECT_EQ(s.pop(), 42);
}

TEST(Stack, HandlesNegativeAndLargeValues) {
  Stack s;
  s.push(-7);
  s.push(INT64_MAX);
  s.push(INT64_MIN);
  EXPECT_EQ(s.pop(), INT64_MIN);
  EXPECT_EQ(s.pop(), INT64_MAX);
  EXPECT_EQ(s.pop(), -7);
}

TEST(Stack, RefillAfterUnderflow) {
  Stack s;
  s.push(5);
  EXPECT_EQ(s.pop(), 5);
  EXPECT_EQ(s.pop(), 0); // underflow
  s.push(9);             // stack still usable after underflow
  EXPECT_EQ(s.pop(), 9);
}