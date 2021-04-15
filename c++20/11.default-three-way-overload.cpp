// Default three-way operator overloads
#include <iostream>
#include <compare>

template<typename T>
struct comp_pair {
    T first, second;

    [[nodiscard]] auto operator <=> (const comp_pair&) const = default;
};

int main(int argc, char const *argv[])
{
    comp_pair<int> x {
        .first = 4,
        .second = 5
    };

    comp_pair<int> y {
        .first = 7,
        .second = 2
    };

    if(x < y) {std::cout << "less\n";}
    if(x <= y) {std::cout << "less or equal\n";}
    if(x > y) {std::cout << "greater\n";}
    if(x >= y) {std::cout << "greater or equal\n";}
    if(x == y) {std::cout << "equal\n";}
    if(x != y) {std::cout << "not equal\n";}

    return 0;
}
