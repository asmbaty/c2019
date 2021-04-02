// Views
#include <iostream>
#include <ranges>
#include <concepts>
#include <algorithm>

int main(int argc, char const *argv[])
{
    auto is_prime = [](const std::integral auto& value) {
        if(value < 2) {
            return false;
        }
        for(auto i=2; i*i <= value; ++i) {
            if(value % i == 0) {
                return false;
            }
        }
        return true;
    };
    auto is_less = [](int num) { return [num](const auto& value){return value<num;};};

    auto prime_nums = std::views::iota(1, 200)
        | std::ranges::views::drop_while(is_less(100))
        | std::ranges::views::filter(is_prime)
        | std::ranges::views::take(10);

    
    auto print = [](const auto& value) { std::cout << value << ' ';};
    std::cout << "First 10 prime numbers starting from 100: ";
    std::ranges::for_each(prime_nums, print);
    std::cout << std::endl;

    // Uneffective code: views are lazily evaluated
    auto custom_view = prime_nums
        | std::ranges::views::reverse
        | std::ranges::views::take(3);
    
    std::cout << "Last three of them in reveresed order: ";
    std::ranges::for_each(custom_view, print);
    std::cout << std::endl;
    
    return 0;
}
