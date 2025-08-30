#include <cassert>
#include <cstdint>

#include "../include/bmath.hh"

using namespace bmath;

int main() {
  constexpr uint64_t four{4}, five{5};
  constexpr mint<uint64_t> mintfour{four};
  constexpr mint<uint64_t> mintfive{five};

  constexpr auto mintnine = mintfour + mintfive;
  static_assert(four + five == mintnine.get());
  static_assert(mintnine == four + five);

  static_assert(4 + 5 == mint<uint64_t>{9});
  static_assert(mint<uint64_t>{8} == 4 + 3);

  return 0;
}
