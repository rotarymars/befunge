/*
 * code.hpp
 *
 * This tracks the current state of the code
 */

#include <cstdint>

class Vec {
  int64_t x_, y_;
};

constexpr int64_t CHUNK_SIZE = (1 << 6);

class BLOCK {
  int64_t cell[CHUNK_SIZE * CHUNK_SIZE];
};
