/// Concepts = type constraints
#include <iostream>
#include <concepts>
#include <functional>

template<std::convertible_to<bool> T, std::convertible_to<bool> U>
auto conjunction(T const& x, U const& y) -> bool {
    bool bx = x, by = y;
    return bx & by;
}

template<typename T, typename U>
    requires std::convertible_to<T, bool> && std::convertible_to<U, bool>
auto disjunction(T const& x, U const& y) -> bool {
    bool bx = x, by = y;
    return bx | by;
}

// trailing requires clause
template<class T>
void LogSquare(T const& x) requires
    requires(T x) {std::cout << x;} &&
    requires(T x) { x*x;}
{
    std::cout << "the square of: " << x << " is " << x*x << '\n';
}

int main(int argc, char const *argv[])
{
    if( conjunction(6.12, 12.6)) {
        std::cout << "double is convertible to bool\n";
    }

    if( !disjunction(NULL, 0)) {
        std::cout << "both NUll and 0 interpreted as false\n";
    }

    LogSquare(11);

    return 0;
}
