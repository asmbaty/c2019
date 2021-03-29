/// Concepts
#include <iostream>
#include <vector>
#include <list>
#include <ranges>
#include <algorithm>

/// small num
template<typename T>
concept SmallNum = sizeof(T) <= 4;
// => float models the concept while double doesn't model the concept

/// incrementable
template<typename T>
concept Incrementable = requires(T x) { x++; ++x;};

/// sortable
template<typename T>
concept Sortable = requires(T x) { std::ranges::sort(x);};

void PrintSorted(Sortable auto& container) {
    decltype(container) copy = container;
    std::ranges::sort(copy);
    for(auto&& elem : copy) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector v {5,2,3,4,1,6};
    PrintSorted(v);

    // std::list l {5,2,3,4,1,6};
    // PrintSorted(l); // error: unsatisfied constraints

    return 0;
}
