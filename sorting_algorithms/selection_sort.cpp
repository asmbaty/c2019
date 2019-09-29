// Selection sort
#include <iostream>
#include <vector>
#include <algorithm>

void insertion_sort(std::vector<int>& arr)
{
    for(auto iter = arr.begin(); iter != arr.end(); ++iter) {
        auto min = std::min_element(iter, arr.end());
        static_assert( std::is_same<decltype(iter), decltype(min)>::value);
        std::swap(*iter, *min);
    }
}

int main(int argc, char const *argv[])
{
    std::vector<int> arr {5, 2, 3, 4, 1};
    insertion_sort(arr);
    for(const auto& elem : arr) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
    
    return EXIT_SUCCESS;
}
