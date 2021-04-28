// latch - single-use thread coordination point
#include <iostream>
#include <chrono>
#include <latch>
#include <syncstream>
#include <vector>
#include <thread>

int main(int argc, char const *argv[])
{
    const int thread_count = 10;
    std::latch lock {thread_count};

    std::vector<std::jthread> threads;
    for(int i{0}; i<thread_count; ++i) {
        threads.push_back(std::jthread { [&lock, i]{
            std::this_thread::sleep_for(std::chrono::milliseconds(i*50));
            std::osyncstream { std::cout } << "thread " << i << " finished and waiting for the latch\n";

            // All the threads wait at this point and continue together
            lock.arrive_and_wait();

            std::osyncstream { std::cout } << "after latch: " << i << '\n';
        }});
    }

    return 0;
}
