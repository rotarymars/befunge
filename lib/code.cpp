#include "code.hpp"

#include <algorithm>
#include <istream>

Block::Block() {
  std::fill(cell, cell + CHUNK_SIZE * CHUNK_SIZE, static_cast<int64_t>(32));
}

int64_t Block::operator[](int64_t index) const { return cell[index]; }

int64_t &Block::operator[](int64_t index) { return cell[index]; }

Vec FungeSpace::blockOf(Vec v) const {
  return Vec{v.x >> CHUNK_SHIFT, v.y >> CHUNK_SHIFT};
}

int64_t FungeSpace::localIndexOf(Vec v) const {
  return (v.y & CHUNK_MASK) * CHUNK_SIZE + (v.x & CHUNK_MASK);
}

int64_t FungeSpace::get(Vec v) const {
  auto it = blocks.find(blockOf(v));
  if (it == blocks.end()) {
    return 32;
  } else {
    return it->second[localIndexOf(v)];
  }
}

void FungeSpace::put(Vec v, int64_t value) {
  blocks[blockOf(v)][localIndexOf(v)] = value;
  if (value != 32) {
    lo_.x = std::min(lo_.x, v.x);
    lo_.y = std::min(lo_.y, v.y);
    hi_.x = std::max(hi_.x, v.x);
    hi_.y = std::max(hi_.y, v.y);
  }
}

FungeSpace::FungeSpace()
    : lo_{INT64_MAX, INT64_MAX}, hi_{INT64_MIN, INT64_MIN} {}

Vec FungeSpace::min() const { return lo_; }

Vec FungeSpace::max() const { return hi_; }

void FungeSpace::load(std::istream &is) {
  int64_t x = 0, y = 0;
  char c;
  while (is.get(c)) {
    if (c == '\n') {
      x = 0;
      y++;
    } else if (c == '\r') {
      // CR
    } else {
      put({x, y}, static_cast<int64_t>(c));
      x++;
    }
  }
}

void Stack::push(int64_t value) {
  data.push_back(value);
  return;
}

int64_t Stack::pop() {
  if (data.empty()) {
    return static_cast<int64_t>(0);
  }
  int64_t value = data.back();
  data.pop_back();
  return value;
}

int64_t Stack::peek() const {
  if (data.empty()) {
    return static_cast<int64_t>(0);
  }
  return data.back();
}

bool Stack::empty() const { return data.empty(); }

std::size_t Stack::size() const { return data.size(); }
