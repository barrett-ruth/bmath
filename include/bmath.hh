#ifndef BMATH_HEADER_ONLY_MATH_LIB
#define BMATH_HEADER_ONLY_MATH_LIB

#include <compare>
#include <concepts>
#include <optional>

namespace bmath {

template <std::integral IntegralType, typename Modulus = std::nullopt_t>
  requires(std::integral<Modulus> || std::is_same_v<Modulus, std::nullopt_t>)
class mint {
 public:
  [[nodiscard]] constexpr explicit mint() : value{} {}
  [[nodiscard]] constexpr explicit mint(IntegralType _value) : value{_value} {}
  [[nodiscard]] constexpr explicit operator IntegralType() const noexcept {
    return value;
  }

  template <typename OtherIntegralType, typename OtherModulus>
  [[nodiscard]] constexpr mint operator+(
      mint<OtherIntegralType, OtherModulus> const& otherMint) const noexcept {
    return mint{value + otherMint.value};
  }

  [[nodiscard]] constexpr mint& operator-(mint const& other) const noexcept {}
  [[nodiscard]] constexpr mint& operator*(mint const& other) const noexcept {}
  [[nodiscard]] constexpr mint& operator/(mint const& other) const noexcept {}
  [[nodiscard]] constexpr mint& operator%(mint const& other) const noexcept {}

  friend constexpr bool operator==(std::convertible_to<IntegralType> auto a,
                                   mint const& b) noexcept {
    return static_cast<IntegralType>(a) == b.value;
  }

  friend constexpr bool operator==(
      mint const& a, std::convertible_to<IntegralType> auto b) noexcept {
    return a.value == static_cast<IntegralType>(b);
  }

  template <typename OtherIntegralType, typename OtherModulus>
  [[nodiscard]] constexpr bool operator==(
      mint<OtherIntegralType, OtherModulus> const& otherMint) const noexcept {
    return value == otherMint.value;
  }

  [[nodiscard]] constexpr IntegralType get() const { return value; }

 private:
  IntegralType value{};
};

}  // namespace bmath

#endif
