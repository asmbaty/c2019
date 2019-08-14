// Threads: Atomic Operations
#include <iostream>
#include <atomic>
#include <chrono>
#include <string>
#include <thread>
using namespace std::chrono_literals;

// Safe to call from different threads and change the value
std::atomic<int> value = 0;

void value_changer(const std::string name, int delta, std::chrono::duration<float> deltaTime)
{
    while(true) {
        std::this_thread::sleep_for(deltaTime);
        std::cout << name << " change the value to: " << (value += delta) << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1 { value_changer, "INCREMENTER", 1, 0.77s};
    std::thread t2 { value_changer, "DECREMENTER", -1, 1.57s};

    std::this_thread::sleep_for(10s);

    t1.detach();
    t2.detach();

    return 0;
}
