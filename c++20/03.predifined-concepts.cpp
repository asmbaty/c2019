/// Predefined Concepts
#include <iostream>
#include <concepts>
#include <cmath>

auto round_to_int(std::floating_point auto x) -> int {
    if(std::fmod(x, decltype(x)(1.0)) <= decltype(x)(0.5)) {
        return static_cast<int>(x);
    }
    return static_cast<int>(x)+1;
}

auto get_result(std::invocable<int> auto const& invoc, int param) -> auto {
    return invoc(param);
}

template <typename T>
concept DefautlAndCopyConstructible = std::default_initializable<T> && std::copy_constructible<T>;

template<DefautlAndCopyConstructible T>
auto copy_from_default() -> T {
    T x = {};
    T y {x};
    return y;
}

int main(int argc, char const *argv[])
{
    std::cout << round_to_int(17.5) << '\n';
    std::cout << round_to_int(17.6) << '\n';

    std::cout << get_result([](int x) {return x*x;}, 7) << '\n';
    get_result([](int x) {std::cout << "param is: " << x << '\n';}, 7);

    double y = copy_from_default<double>();
    std::cout << y << '\n';

    return 0;
}
