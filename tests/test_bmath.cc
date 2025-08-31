#include <gtest/gtest.h>

#include <cstdint>
#include <format>

#include "../include/bmath.hh"

using namespace bmath;

TEST(MintTest, BasicConstruction) {
  mint<uint64_t> four{4};

  static_assert(std::is_trivially_copyable_v<mint<uint64_t>>);

  EXPECT_EQ(four.get(), 4);
}

TEST(MintTest, Formatting) {
  mint<uint64_t> four{4};

  auto formatted = std::format("{}", four);
  EXPECT_EQ(formatted, "4");

  auto string_result = to_string(four);
  EXPECT_EQ(string_result, "4");
}

TEST(MintTest, Addition) {
  mint<uint64_t> a{3};
  mint<uint64_t> b{5};

  auto result = a + b;
  EXPECT_EQ(result.get(), 8);
}

TEST(MintTest, Subtraction) {
  mint<uint64_t> a{10};
  mint<uint64_t> b{3};

  auto result = a - b;
  EXPECT_EQ(result.get(), 7);
}

TEST(MintTest, Multiplication) {
  mint<uint64_t> a{6};
  mint<uint64_t> b{7};

  auto result = a * b;
  EXPECT_EQ(result.get(), 42);
}

TEST(MintTest, Modular) {
  constexpr uint64_t mod = 13;
  mint<uint64_t, mod> a{15};

  EXPECT_EQ(a.get(), 2);
}

TEST(PowerTest, BasicPower) {
  mint<uint64_t> base{2};
  auto result = pow(base, 3);
  EXPECT_EQ(result.get(), 8);
}

TEST(PowerTest, PowerOfOne) {
  mint<uint64_t> base{5};
  auto result = pow(base, 0);
  EXPECT_EQ(result.get(), 1);
}

TEST(PowerTest, PowerOfZero) {
  mint<uint64_t> base{0};
  auto result = pow(base, 5);
  EXPECT_EQ(result.get(), 0);
}
