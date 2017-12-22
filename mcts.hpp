#pragma once
#include <memory>
#include <random>
#include <vector>
#include "board.hpp"

class Result {
 public:
  Hand hand;
};

class Node {
 public:
  Node() : Node(initial_board()) {}
  explicit Node(const board &bd)
    : bd(bd), children(), cnt(0), win(0) {}
  Node(const Node &) = default;
  Node(Node &&) = default;
  Node &operator=(const Node &) = default;
  Node &operator=(Node &&) = default;
  void expand();
  bool is_leaf() const;
  Node* select(int64_t t) const;
  board bd;
  std::vector<Node> children;
  int cnt;
  double win;
};

class MCTS {
 public:
  Result think(const board &);
  double playout(const board &);
  Node root;
  std::mt19937 mt;
};
