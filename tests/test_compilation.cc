#include <cassert>
#include <cstdint>
#include <iostream>

#include "../include/bmath.hh"

using namespace bmath;
using namespace std;

int main() {
  mint<uint64_t> four{4};

  // should be trivially copyable
  static_assert(is_trivially_copyable_v<mint<uint64_t>>);

  // should be able to format
  auto formatted = format("{}\n", four);

  // and use to_string
  formatted = to_string(four);

  return 0;
}
