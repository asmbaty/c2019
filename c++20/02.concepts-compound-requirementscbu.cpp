/// Concepts - Compound Requirements
#include <iostream>
#include <concepts>
#include <ranges>
#include <algorithm>

// Type that has a swap method that returns no value
template<typename T>
concept Swappable = requires(T x, T y) {
    { x.swap(y) } -> std::same_as<void>;
};

// Type that has a size() method with return value convertible to size_t
template<typename T>
concept Sizeable = requires(T x) {
    { x.size() } -> std::convertible_to<std::size_t>;
};

template<typename T>
concept ComplicatedConcept = Swappable<T> && Sizeable<T>;

// Comparable type
template<typename T>
concept Comparable = requires(T x, T y) {
    { x == y } -> std::convertible_to<bool>;
    { x < y } -> std::convertible_to<bool>;
};

class SwapClass
{
public:
    // int swap(SwapClass& x) { return 123;}
    void swap(SwapClass& x) { }
    std::size_t size() {
        return 0;
    }
};

void some_function(ComplicatedConcept auto const& object) {}

int main(int argc, char const *argv[])
{
    SwapClass swapobj;
    some_function(swapobj);

    return 0;
}
