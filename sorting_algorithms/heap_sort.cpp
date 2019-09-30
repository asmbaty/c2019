// Quick sort
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void heapify(std::vector<int>& arr, int len, int n)
{
    int largest = n;
    int l = (n<<1)+1; // left child
    int r = (n<<1)+2; // right child
    if(l < len && arr[l] > arr[largest]) {
        largest = l;
    }
    if(r < len && arr[r] > arr[largest]) {
        largest = r;
    }
    if(n != largest) {
        std::swap(arr[n], arr[largest]);

        heapify(arr, len, largest);
    }
}

void heap_sort(std::vector<int>& arr)
{
    int n = static_cast<int>(arr.size());
    // make heap. (n-1)>>1 is the parent of the last element
    for(int i=(n-1)>>1; i>=0; --i) {
        heapify(arr, n, i);
    }
    assert(std::is_heap(begin(arr), end(arr)));
    while(n --> 0) {
        std::swap(arr[0], arr[n]);
        heapify(arr, n, 0);
    }
}

int main(int argc, char const *argv[])
{
    std::vector<int> arr {5, 10, 3, 4, 8, 1, 7, 2, 9, 6 };
    heap_sort(arr);
    for(const auto& elem : arr) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
