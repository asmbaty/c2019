// Ranges
#include <iostream>
#include <ranges>
#include <span>
#include <vector>
#include <algorithm>
#include <numeric>

int main(int argc, char const *argv[])
{
    // vector of pairs
    std::vector<std::pair<int, std::string>> vec = { 
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"}
    };
    
    // sort the vector accorind to the second elements
    std::ranges::sort(vec, {}, &std::pair<int, std::string>::second);

    std::cout << "print numbers sorted according to their names\n";
    
    std::ranges::for_each(vec
        , [](const auto& str) { std::cout << str << '\n';}
        , [](const auto& pair) { return std::to_string(pair.first) + "-" + pair.second;} );
    
    return 0;
}
