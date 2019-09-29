// Insertion sort
#include <iostream>
#include <vector>
#include <algorithm>

void insertion_sort(std::vector<int>& arr)
{
    for(int i=0; i<arr.size(); ++i) {
        for(int j=i; j>0 && arr[j] < arr[j-1]; --j) {
            std::swap(arr[j], arr[j-1]);
        }
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
