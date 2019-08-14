// Threads: Mutual Exclusions - Call Once
#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
using namespace std::chrono_literals;

std::once_flag init_once;
std::mutex mtx;
std::shared_ptr<int> ptr;

void initialize_shared_resources()
{
    std::cout << "Initializing resources..\n";
    ptr.reset(new int);
    std::cout << "Initialization is done\n";
}

void access()
{
    std::call_once(init_once, initialize_shared_resources);
    std::shared_ptr<int> cur = ptr;
    std::cout << "Shared use count: " << ptr.use_count() << '\n';
    std::this_thread::sleep_for(1s);
}

int main(int argc, char const *argv[])
{
    std::vector<std::thread> threads;
    for(int i=0;i<10;++i) {
        threads.push_back(std::thread{access});
        std::this_thread::sleep_for(0.05s);
    }

    for(auto& t : threads) {
        t.join();
    }

    std::cout << "[MAIN] Shared use count: " << ptr.use_count() << '\n';

    return 0;
}
