#include "hand.hpp"
#include <cassert>

std::string to_string(Hand h) {
  int hnum = static_cast<int>(h);
  assert(hnum >= 0 && hnum <= 64);
  if (hnum > 64) return "PASS";
  std::string res;
  res += 'A' + hnum%8;
  res += '1' + hnum/8;
  return res;
}
