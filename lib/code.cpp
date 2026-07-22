#include "code.hpp"

#include <algorithm>

Block::Block() {
  std::fill(cell, cell + CHUNK_SIZE * CHUNK_SIZE, static_cast<int64_t>(32));
}