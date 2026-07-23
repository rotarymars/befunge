#include "code.hpp"

#include <algorithm>

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

void FungeSpace::put(Vec, int64_t value) {
  auto &block = blocks[blockOf(v)];
  block[localIndexOf(v)] = value;
  if (blocks.size() == 1) {
    lo_ = hi_ = v;
  } else {
    lo_.x = std::min(lo_.x, v.x);
    lo_.y = std::min(lo_.y, v.y);
    hi_.x = std::max(hi_.x, v.x);
    hi_.y = std::max(hi_.y, v.y);
  }
}