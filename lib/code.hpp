#ifndef CODE_HPP
#define CODE_HPP
/*
 * code.hpp
 *
 * This tracks the current state of the code
 */

#include <cstdint>

class Vec {
  public:
    int64_t x, y;
};

constexpr int64_t CHUNK_SIZE = (1 << 6);

class Block {
  int64_t cell[CHUNK_SIZE * CHUNK_SIZE];
};
#endif