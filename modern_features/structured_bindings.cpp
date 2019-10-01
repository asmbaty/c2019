#include <iostream>
#include <array>
#include <map>
#include <tuple>
#include <cassert>

// C++17 Structured Bindings with arrays
void sb_arrays()
{
    std::array<int, 3> arr = {1, 2, 3 };
    if(auto& [x, y, z] = arr; x<y && y<z ) { // Initializer in the if statement
        std::swap(x, z);
    }
    for(auto v: arr) std::cout << v << ' '; // 3, 2, 1
    std::cout << std::endl;
}

// C++17 Structured Bindings with pairs
void sb_pair()
{
    std::map<std::string_view, int> age;
    if(auto [iter, success] = age.insert({"Arthur", 15}); success) {
        // Inserted successfully
    }
    if(auto [iter, success] = age.insert({"Arthur", 18}); success) {
        assert(("Success must be false", 0));
    }
    age.insert({"Tereza", 18});
    age.insert({"Lolita", 17});
    // Increase the ages of everyone by one
    for(auto& [name, val] : age) {
        ++val;
    }
    for(auto& [name, val] : age) {
        std::cout << name << "-->" << val << '\n';
    }
}

// C++17 Structured Bindings with tuples
void sb_tuple()
{
    std::tuple<int, std::string, int> s {3, "three", 9};
    auto [n, l, nn] = s;
    std::cout << n << ' ' << nn << '\n';
}

int main(int argc, char const *argv[])
{
    sb_arrays();
    sb_pair();
    sb_tuple();

    return EXIT_SUCCESS;
}
