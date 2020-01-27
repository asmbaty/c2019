// Memory pool
#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <bitset>
#include <cassert>
#include <map>
#include <vector>
#include <future>

using namespace std::chrono_literals;

/// @brief Written for learning purposes only
///        Not even tested in a real-use application
template<typename TYPE, int COUNT, int SIZE>
class memory_pool
{
public:
    memory_pool()
    {
        // initialize index_map;
        for(int i=0; i<COUNT; ++i) {
            index_map[array[i].data()] = i;
        }
    }

    TYPE* allocate_node()
    {
        if(COUNT == used_count) {
            return nullptr;
        }
        while(used_mask[current_index]) {
            ++current_index;
            if(current_index == COUNT) {
                current_index = 0;
            }
        }
        used_mask[current_index] = true;
        ++used_count;
        return array[current_index].data();
    }

    unsigned count() const
    {
        return used_count;
    }

    void deallocate_node(TYPE* pointer)
    {
        assert(index_map.find(pointer) != index_map.end());
        used_mask[index_map[pointer]] = false;
        --used_count;
    }

private:
    std::array<TYPE, SIZE> array[COUNT];
    std::bitset<COUNT> used_mask;
    std::map<TYPE*, unsigned> index_map;
    unsigned used_count {0};
    unsigned current_index {0};
};

int main(int argc, char const *argv[])
{
    memory_pool<char, 100, 1000> mp;
    auto p = mp.allocate_node();
    p[0] = 'c'; p[1] = 'a'; p[2] = 'r'; p[3] = '\0';
    std::cout << p << '\n';
    std::cout << mp.count() << '\n';
    mp.deallocate_node(p);
    std::cout << mp.count() << '\n';

    return 0;
}
