#pragma once
#include <string>
#include <vector>
#include "hand.hpp"

class board {
 public:
  board(uint64_t me, uint64_t op) : me(me), op(op) {}
  board(const board &) = default;
  board &operator=(const board &) = default;
  uint64_t me, op;
};

inline board initial_board() {
  return board(UINT64_C(0x0000000810000000), UINT64_C(0x0000001008000000));
}

board to_board(const std::string &);
std::string to_string(const board &);
uint64_t flip(const board &, Hand);
uint64_t mobility(const board &);
std::vector<board> next_states(const board &);
board move(const board &, Hand);
Hand hand_from_diff(const board &prev, const board &now);
