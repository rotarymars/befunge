#ifndef CODE_HPP
#define CODE_HPP
/*
 * code.hpp
 *
 * This tracks the current state of the code
 */

#include <cstdint>
#include <functional>

class Vec {
  public:
    int64_t x, y;
    bool operator==(const Vec&) const = default;
};

constexpr int64_t CHUNK_SIZE = (1 << 6);

class Block {
  private:
    int64_t cell[CHUNK_SIZE * CHUNK_SIZE];
  public:
    Block();
    int64_t operator[](int64_t) const;
    int64_t& operator[](int64_t);
};

template <>
struct std::hash<Vec> {
  std::size_t operator()(const Vec& v) const noexcept {
    std::size_t h1 = std::hash<size_t>{}(v.x);
    std::size_t h2 = std::hash<size_t>{}(v.y);
    return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2)); // this is a magic hash that works...
  }
};

class FungeSpace {
  private:
    std::unordered_map<Vec, Block> blocks;
    Vec lo_,hi_;
  public:
    int64_t get(Vec) const;
    void put(Vec&, int64_t);
    Vec min() const;
    Vec max() const;
};

#endif