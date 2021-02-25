// Quick sort
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

size_t partition(std::vector<int>& arr, size_t left, size_t right)
{
    size_t pivot = arr[right]; // pivot is the last element
    for(size_t i=left; i<right; ++i) {
        if(arr[i] < pivot) {
            std::swap(arr[i], arr[left]);
            ++left;
        }
    }
    std::swap(arr[left], arr[right]); // put the pivot at its place
    return left; // return the position of the pivot element
}

void quick_sort(std::vector<int>& arr, size_t left, size_t right)
{
    // sort the interval [left, right]
    if(left < right) {
        size_t pivot = partition(arr, left, right);
        if(pivot) { // to ensure (pivot-1) is positive
            quick_sort(arr, left, pivot - 1ul);
        }
        quick_sort(arr, pivot+1, right);
    }
}

void quick_sort(std::vector<int>& arr)
{
    quick_sort(arr, 0ul, arr.size()-1ul);
}

int main(int argc, char const *argv[])
{
    std::vector<int> arr {5, 10, 3, 4, 8, 1, 7, 2, 9, 11, 6 };
    quick_sort(arr);
    for(const auto& elem : arr) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
