// Overload spaceship operator
#include <iostream>
#include <concepts>

template<typename T>
    requires requires(T x, T y) {{x+y} -> std::same_as<T>;}
struct sum_pair {
    T first, second;

    // overload operator = and <=> operators for the 6 comparison operators to work
    // C++20: 'operator =' automatically overloads 'operator !='

    [[nodiscard]] std::weak_ordering operator <=> (const sum_pair& rhs) const {
        return first + second <=> rhs.first + rhs.second;
    }

    [[nodiscard]] bool operator == (const sum_pair& rhs) const {
        return first + second == rhs.first + rhs.second;
    }
};

int main(int argc, char const *argv[])
{
    sum_pair<int> x {
        .first = 4,
        .second = 5
    };

    sum_pair<int> y {
        .first = 1,
        .second = 10
    };

    if(x != y) {std::cout << "not equal\n";}
    if(x <= y) {std::cout << "less or equal\n";}

    return 0;
}
