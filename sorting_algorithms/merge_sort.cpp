// Merge sort
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void merge(std::vector<int>& arr, size_t l, size_t mid, size_t r)
{
    assert(l<=mid && mid+1<=r);
    auto n = mid - l + 1ul;
    auto m = r - mid;
    int larr[n], rarr[m];
    std::copy_n(arr.begin()+l, n, larr);
    std::copy_n(arr.begin()+mid+1, m, rarr);
    int i = 0, j = 0;
    decltype(l) k = l;
    while (i<n && j<m) {
        if(larr[i] <= rarr[j]) {
            arr[k++] = larr[i++];
        } else {
            arr[k++] = rarr[j++];
        }
    }
    while (i<n) {
        arr[k++] = larr[i++];
    }
    while (j<m) {
        arr[k++] = rarr[j++];
    }
    assert(k == r+1);
}

void merge_sort(std::vector<int>& arr, size_t l, size_t r)
{
    if(r - l > 0) {
        auto mid = (l+r)>>1ul;
        merge_sort(arr, l, mid);
        merge_sort(arr, mid+1, r);
        merge(arr, l, mid, r);
    }
}

void merge_sort(std::vector<int>& arr)
{
    if(!arr.empty()) { 
        merge_sort(arr, 0ul, arr.size()-1u);
    }
}

int main(int argc, char const *argv[])
{
    std::vector<int> arr {5, 10, 3, 4, 8, 1, 7, 2, 9, 6 };
    merge_sort(arr);
    for(const auto& elem : arr) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
