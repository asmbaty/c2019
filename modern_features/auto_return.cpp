#include <iostream>
#include <type_traits>

// C++14 Function return type deduction
template<typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x+y)
{
    return x+y;
}

// C++14 Function return type deduction
auto what_is_my_name()
{
    return __func__;
}

int main(int argc, char const *argv[])
{
    // C++17 If initializer
    if(int x = 17; x) {
        std::cout << "non zero value inserted: " << x << '\n';
    }

    std::cout << "the result of (5,6) is: " << (5,6) << '\n';

    auto x = add(4ll, 5.0f); // long long + float = float
    if(std::is_same_v<decltype(x), float>) {
        std::cout << "long long + float = float" << std::endl;
    }

    std::cout << "typeid(what_is_my_name): " << typeid(what_is_my_name).name() << '\n';
    std::cout << "return value(what_is_my_name): " << what_is_my_name() << '\n';

    return EXIT_SUCCESS;
}
