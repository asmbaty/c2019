// barrier
#include <iostream>
#include <concepts>
#include <barrier>
#include <array>
#include <thread>

bool is_prime(std::integral auto n) {
    if(n<2) {return false;}
    for(decltype(n) i=2;i*i<=n;++i) {
        if(n%i==0) {
            return false;
        }
    }
    return true;
}

auto next_prime(std::integral auto n) {
    do {
        n++;
    } while(!is_prime(n));
    return n;
}

int main(int argc, char const *argv[])
{
    // generate triples of big prime numbers
    int64_t prime1, prime2, prime3;

    // nofity when next three primes are ready
    std::barrier generated {3, [&prime1, &prime2, &prime3]{
        std::cout << "triple of primes: {" << prime1 << "} {" << prime2 << "} {" << prime3 << "}\n";
    }};

    auto generate_primes = [&generated](int64_t from, int64_t& output) {
        int count = 10;
        while(count-- != 0) {
            output = from = next_prime(from);
            generated.arrive_and_wait();
        }
    };

    int64_t init = 10000000000000000ll;

    std::array<std::thread, 3> threads {
        std::thread{generate_primes, init, std::ref(prime1)},
        std::thread{generate_primes, 2*init, std::ref(prime2)},
        std::thread{generate_primes, 3*init, std::ref(prime3)}
    };

    for(auto& thread : threads) {
        thread.join();
    }

    return 0;
}
