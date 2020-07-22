// Threads with Member Functions and Lambdas
#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
using namespace std::chrono_literals;

bool is_prime(int x)
{
    if(x<2) return false;
    for(int i = 2; i*i <= x; ++i) {
        if(x%i == 0) {
            return false;
        }
    }
    return true;
}

class primes_generator
{
public:
    void search()
    {
        for(int i = 1; ; i++) {
            if(is_prime(i)) {
                std::cout << "prime: " << i << '\n';
            }
            std::this_thread::sleep_for(0.13s);
        }
    }
};

int main(int argc, char const *argv[])
{
    auto beeper = [](){
        for(int i=1;;++i) {
            std::this_thread::sleep_for(1s);
            std::cout << i << " seconds passed\a" << std::endl;
        }
    };

    primes_generator pg;

    std::thread ttimer { std::ref(beeper) };
    std::thread tpg { &primes_generator::search, &pg };

    std::this_thread::sleep_for(10s);

    ttimer.detach();
    tpg.detach();

    return 0;
}
