#include "mcts.hpp"
#include <cassert>
#include <iostream>

double ucb1(double w, int64_t s, int64_t t) {
  double sd = s+1, td = t+1;
  return w/sd + sqrt(2*log(td)/sd);
}

void Node::expand() {
  assert(children.empty());
  const auto nexts = next_states(bd);
  for (const auto &next : nexts) {
    children.emplace_back(next);
  }
}

bool Node::is_leaf() const {
  return children.empty();
}

Node* Node::select(int64_t t) const {
  assert(!is_leaf());
  Node* res = const_cast<Node*>(children.data());
  double max_val = 0;
  for (const auto &child : children) {
    double val = ucb1(child.win, child.cnt, t);
    if (val > max_val) {
      max_val = val;
      res = const_cast<Node*>(&child);
    }
  }
  return res;
}

Result MCTS::think(const board &bd) {
  root = Node(bd);
  root.expand();
  constexpr int64_t loop = 1000000000;
  for (int64_t i = 0; i < loop; ++i) {
    std::vector<Node*> nodes;
    Node* node = &root;
    nodes.push_back(node);
    while (!node->is_leaf()) {
      node = node->select(i);
      nodes.push_back(node);
    }
    node->expand();
    if (!node->is_leaf()) {
      node = node->select(i);
      nodes.push_back(node);
    }
    double win = playout(node->bd);
    while (!nodes.empty()) {
      nodes.back()->win += win;
      nodes.back()->cnt++;
      nodes.pop_back();
      win = 1.0 - win;
    }
    if ((i % 100000) == 99999) {
      for (const auto &child : root.children) {
        double winlate = child.win / child.cnt;
        Hand hc = hand_from_diff(bd, child.bd);
        std::cerr << child.win << ' ' << child.cnt << ' ' << winlate << ' ' << to_string(hc) << std::endl;
      }
    }
  }
  double max_winlate = 0;
  Hand h;
  for (const auto &child : root.children) {
    double winlate = child.win / child.cnt;
    Hand hc = hand_from_diff(bd, child.bd);
    std::cerr << winlate << ' ' << to_string(hc) << std::endl;
    if (winlate > max_winlate) {
      max_winlate = winlate;
      h = hand_from_diff(bd, child.bd);
    }
  }
  return (Result){h};
}

double winlose(const board &bd) {
  int pcnt = __builtin_popcount(bd.me);
  int ocnt = __builtin_popcount(bd.op);
  if (pcnt == ocnt) return 0.5;
  return pcnt > ocnt ? 1.0 : 0.0;
}

double MCTS::playout(const board &bd) {
  const auto nexts = next_states(bd);
  if (nexts.empty()) return winlose(bd);
  std::uniform_int_distribution<int> dis(0, nexts.size()-1);
  return 1.0 - playout(nexts[dis(mt)]);
}
