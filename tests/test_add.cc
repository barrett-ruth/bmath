#include <cassert>
#include <cstdint>
#include <iostream>

#include "../include/bmath.hh"

using namespace bmath;
using namespace std;

int main() {
  constexpr uint64_t four{4}, five{5};
  constexpr mint<uint64_t> mintfour{four};
  constexpr mint<uint64_t> mintfive{five};

  constexpr auto mintnine = mintfour + mintfive;
  // static_assert(mintnine == four + five);

  // static_assert(4 + 5 == mint<uint64_t>{9});
  static_assert(mint<uint64_t, 100000>{8} ==
                mint<uint64_t, 100000>{4} + mint<uint64_t, 100000>{4});

  static_assert(is_trivially_copyable_v<mint<uint64_t>>);

  // pow(mint<int>{2}, 0);

  // cout << (std::format("x: {}\n", mintfour));

  // auto res = mint<int>{4} + mint<int, 5>{4};

  // cout << (mint<int, 4>{5} + mint<int, 4>{7});
  // cout << pow(mint<int, 5>{4}, 5);

  cout << (pow(mint<int>{5}, 5));

  return 0;
}
