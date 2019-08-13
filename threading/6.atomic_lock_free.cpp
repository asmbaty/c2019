// Threads: Atomic Operations - Lock Free Types
#include <iostream>
#include <atomic>
#include <chrono>
#include <string>
#include <thread>
using namespace std::chrono_literals;

struct merger
{
    int a, b;
    int operator () () const
    {
        return a*b;
    }
};

struct complex
{
    double x;
    complex() = default;
    complex(complex const& other) {x = other.x;};
};

int main(int argc, char const *argv[])
{
    // unsigned int
    std::atomic<unsigned int> ai;
    std::cout << "is unsigned int trivially copyable?: " << std::boolalpha << 
                            std::is_trivially_copyable_v<unsigned int> << '\n';
    std::cout << "is unsigned int lock free?: " << std::boolalpha << ai.is_lock_free() << '\n';

    // merger
    std::atomic<merger> am;
    std::cout << "is merger trivially copyable?: " << std::boolalpha << 
                            std::is_trivially_copyable_v<merger> << '\n';
    std::cout << "is merger lock free?: " << std::boolalpha << am.is_lock_free() << '\n';

    // std::atomic<complex> cm; // ERROR is not trivially copyable
    
    return 0;
}
