#include "code.hpp"

#include <algorithm>

Block::Block() {
  std::fill(cell, cell + CHUNK_SIZE * CHUNK_SIZE, static_cast<int64_t>(32));
}

int64_t Block::operator[](int64_t index) const {
  return cell[index];
}

int64_t& Block::operator[](int64_t index) {
  return cell[index];
}