#include <gtest/gtest.h>

#include <cstdint>
#include <format>

#include "../include/bmath/bmath.hh"

using namespace bmath;

bool naive_prime(size_t n) {
  if (n < 2) {
    return false;
  }
  if (n == 2) {
    return true;
  }
  if (n % 2 == 0) {
    return false;
  }
  for (size_t i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

TEST(SieveTest, BasicConstruction) { Eratosthenes<100> sieve; }

TEST(SieveTest, ValidateAgainstNaive) {
  Eratosthenes<1000> sieve;

  for (size_t i = 0; i <= 1000; ++i) {
    EXPECT_EQ(sieve[i], naive_prime(i))
        << "Sieve disagrees with naive checker for " << i;
  }
}
