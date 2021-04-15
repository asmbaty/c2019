// Three-Way comparison operator
#include <iostream>
#include <cassert>
#include <string>

using namespace std::string_literals;

int main(int argc, char const *argv[])
{
    // the spaceship operator
    std::strong_ordering cmp_strong = ( 4 <=> 5);
    assert(cmp_strong == std::strong_ordering::less);

    std::partial_ordering cmp_partial = (15.0 <=> 7.0);
    assert(cmp_partial == std::partial_ordering::greater);

    // An alternative to std::string::compare
    auto cmp = "abc"s <=> "abe"s;
    if(std::is_eq(cmp)) {
        std::cout << "equal strings" << std::endl;
    }
    if(std::is_lt(cmp)) {
        std::cout << "first string is lesser" << std::endl;
    }
    if(std::is_gt(cmp)) {
        std::cout << "first strings is greater" << std::endl;
    }

    return 0;
}
