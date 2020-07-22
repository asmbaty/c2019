// Static Assertion
#include <iostream>
#include <type_traits>

struct no_copy
{
    no_copy(no_copy const&) = delete;
    no_copy() = default;
};

template<typename T>
class copyable_object
{
    static_assert(std::is_copy_constructible<T>::value, "T required a copy constructor");
};

int main(int argc, char const *argv[])
{
    static_assert( sizeof(void*) == 8, "64-bit compiler is required");
    copyable_object<int> ok; // ok
    copyable_object<no_copy> err; // compile time error

    return 0;
}
