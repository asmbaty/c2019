// overloads with concepts
#include <iostream>
#include <concepts>
#include <limits>
#include <cmath>
#include <span>
#include <vector>

template <std::floating_point T>
bool AreEqual(T x, T y, int precision = 2)
{
    return std::fabs(x - y) <= 1e-6;
}

template <std::integral T>
bool AreEqual(T x, T y)
{
    return x == y;
}

template <typename T, std::size_t N>
int myfind(const T& value, std::span<T, N> data)
{
    for(size_t i=0; i<data.size(); ++i) {
        if(AreEqual(value, data[i])) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int r[] = {1,2,3,4};
    std::cout << myfind(4, std::span{r}) << '\n';
    std::cout << myfind(4, std::span{r, 3}) << '\n';

    std::vector d {1.4, 2.5, 3.6};

    std::cout << myfind(2.5+1e-10, std::span{d}) << '\n';
    
    return 0;
}
