// keys view and values view
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <algorithm>

using namespace std::views;

int main(int argc, char const *argv[])
{
    std::unordered_map<int, std::string> m { {1, "one"}, {2, "two"}, {3, "three"}};

    // print keys
    std::cout << "keys: ";
    for(auto&& i : m | keys) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    // print values
    std::cout << "values: ";
    for(auto&& i : m | values) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    return 0;
}
