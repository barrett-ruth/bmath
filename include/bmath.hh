#ifndef BMATH_HEADER_ONLY_MATH_LIB
#define BMATH_HEADER_ONLY_MATH_LIB

#include <format>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <string>

namespace bmath {

inline constexpr uint64_t DEFAULT_MOD = 1'000'000'007;

template <std::integral T, T M = static_cast<T>(DEFAULT_MOD)>
  requires(M > 0 && DEFAULT_MOD <= std::numeric_limits<T>::max())
class mint {
 public:
  [[nodiscard]] constexpr explicit mint() : value{} {}
  [[nodiscard]] constexpr explicit mint(T t) : value{t % M} {}
  [[nodiscard]] constexpr explicit operator T() const noexcept { return value; }

  template <std::convertible_to<T> OtherT, T OtherM>
    requires(M == OtherM)
  [[nodiscard]] constexpr mint operator+(
      mint<OtherT, OtherM> const other) const noexcept {
    if constexpr (M != 0 && OtherM != 0) {
      static_assert(M == OtherM,
                    "Cannot add integral types with differing moduli");
    } else if (M != 0 && OtherM != 0) {
      assert(M == OtherM && "Cannot add integral types with differing moduli");
    }
    return mint<T, M>{value + other.get()};
  }

  // [[nodiscard]] constexpr mint& operator-(mint const other) const noexcept {}
  // [[nodiscard]] constexpr mint& operator*(mint const other) const noexcept {}
  // [[nodiscard]] constexpr mint& operator/(mint const other) const noexcept {}
  // [[nodiscard]] constexpr mint& operator%(mint const other) const noexcept {}
  [[nodiscard]] constexpr T get() const noexcept { return value; }

  template <std::convertible_to<T> OtherT, OtherT OtherM>
  [[nodiscard]] constexpr bool operator==(
      mint<OtherT, OtherM> const other) const noexcept {
    return get() == static_cast<T>(other.get());
  }

  template <std::convertible_to<T> OtherT>
  [[nodiscard]] constexpr bool operator==(OtherT const other) const noexcept {
    return get() == static_cast<T>(other);
  }

  template <std::convertible_to<T> OtherT, T OtherM>
  friend std::ostream& operator<<(std::ostream& out,
                                  mint<OtherT, OtherM> const other) {
    return out << other.get();
  }

 private:
  T value{};
};

template <std::integral T, T M, std::integral U>
  requires(M >= 0)
[[nodiscard]] static constexpr bmath::mint<T, M> pow(mint<T, M> base,
                                                     U exponent) {
  if (exponent < 0) {
    throw std::domain_error(
        std::format("cannot compute pow({}, {}) with negative exponent {}",
                    base, exponent, exponent));
  }

  if (base == 0) {
    if (exponent == 0) {
      throw std::domain_error("pow(0, 0) is indeterminate");
    }

    return mint<T, M>{0};
  }

  if (base == 1 || exponent == 0) {
    return mint<T, M>{1};
  }

  T t{};

  while (exponent > 0) {
    exponent >>= 1;
  }

  return mint<T, M>{t};
}

template <std::integral T, T M = DEFAULT_MOD>
  requires(M > 0)
[[nodiscard]] std::string to_string(mint<T, M> const number) {
  return std::to_string(number.get());
}

}  // namespace bmath

template <class CharT, std::integral T, T M>
struct std::formatter<bmath::mint<T, M>, CharT> {
  std::formatter<std::basic_string_view<CharT>, CharT> inner;

  constexpr auto parse(std::basic_format_parse_context<CharT>& pc) {
    return inner.parse(pc);
  }

  template <class Ctx>
  auto format(bmath::mint<T, M> const x, Ctx& ctx) const {
    std::basic_string<CharT> tmp;
    if constexpr (std::same_as<CharT, wchar_t>) {
      std::format_to(std::back_inserter(tmp), L"{}", x.get());
    } else {
      std::format_to(std::back_inserter(tmp), "{}", x.get());
    }
    return inner.format(tmp, ctx);
  }
};

#endif
