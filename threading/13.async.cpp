// Threads: Futures - std::sync
#include <iostream>
#include <chrono>
#include <future>
#include <numeric>
#include <thread>
#include <vector>
using namespace std::chrono_literals;

template<typename Iterator>
int parallel_sum(Iterator begin, Iterator end)
{
    auto len = end - begin;
    if(len < 1000)
        return std::accumulate(begin, end, 0);
    auto mid = begin + len/2;
    auto handle = std::async(std::launch::async,
                parallel_sum<Iterator>, mid, end);
    int sum = parallel_sum<Iterator>(begin, mid);
    return sum + handle.get();
}

int main(int argc, char const *argv[])
{
    auto milliseconds_beeper = []() {
        for(int i=1;i<=10;++i) {
            std::this_thread::sleep_for(100ms);
            std::cout << i*100 << " milliseconds passed\n";
        }
    };

    // deferred launch: this would take 2 seconds to complete
    std::future f1 = std::async(std::launch::deferred, milliseconds_beeper);
    std::this_thread::sleep_for(1s);
    f1.get(); // executes when get() is called in the calling thread


    // async launch: this would take 1 seconds to complete
    std::future f2 = std::async(std::launch::async, milliseconds_beeper);
    std::this_thread::sleep_for(1s);
    f2.get(); // executes at async call


    // parallel sum calculator
    std::vector<int> v(12345,1);
    int sum = parallel_sum(v.begin(), v.end());
    std::cout << "sum: " << sum << std::endl;

    return 0;
}
