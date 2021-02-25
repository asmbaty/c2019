#include <iostream>
#include <unordered_set>

struct custom_type
{
    std::string name;
    int age;
};

int main(int argc, char *argv[])
{
    auto hash = [](const custom_type& ct) -> std::size_t {
        return std::hash<std::string>{}(ct.name) ^ std::hash<int>{}(ct.age);
    };

    auto equal = [](const custom_type& ct1, const custom_type& ct2) -> bool {
        return ct1.name == ct2.name && ct1.age == ct2.age;
    };

    std::unordered_set<custom_type, decltype(hash), decltype(equal)> us;
    
    us.emplace("aharon", 12);
    us.emplace("aharon", 29);

    std::cout << us.size() << '\n';

    return 0;
}