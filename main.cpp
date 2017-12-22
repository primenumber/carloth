#include <iostream>
#include <string>
#include "board.hpp"
#include "mcts.hpp"
#include "hand.hpp"

int main() {
  std::string str;
  std::cin >> str;
  board bd = to_board(str);
  for (const auto next : next_states(bd)) {
    std::cerr << to_string(hand_from_diff(bd, next)) << ' ' << to_string(next) << std::endl;
  }
  MCTS mcts;
  auto res = mcts.think(bd);
  std::cout << to_string(res.hand) << std::endl;
  return 0;
}
