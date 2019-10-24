// C++11 Variadic Templates
// C++17 Fold Expression
#include <iostream>
#include <bitset>

template<volatile int *reg>
struct REGISTER
{
  template<int... bits>
  void set_bits()
  {
    *reg |= ( (1<<bits) | ...);
  }
};

template<typename T, T ...bits>
constexpr auto bitty() -> T
{
  T x{0};
  x |= ( (1<<bits) | ...);
  return x;
}

template<typename T>
auto binary_rep(T x) -> void
{
  std::cout << std::bitset<8 * sizeof(decltype(x))>(x) << '\n';
}

int main(int argc, char const* argv[])
{
  volatile static int value = 0;
  REGISTER<&value>().set_bits<1, 3, 5, 15>();
  binary_rep(value);

  constexpr int c1 = bitty<int, 1, 5, 7, 14>();
  constexpr int c2 = bitty<int, 0, 10, 20, 30>();
  binary_rep(c1);
  binary_rep(c2);
  
  return value;
}