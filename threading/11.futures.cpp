// Threads: Futures and Promises
#include <iostream>
#include <chrono>
#include <future>
#include <string>
#include <thread>
using namespace std::chrono_literals;

void bake_the_cake(std::promise<std::string> p)
{
    std::this_thread::sleep_for(2s);
    p.set_value("Pound Cake");
}

void lay_the_table()
{
    // let's bake the cake in another thread
    // and get it's name when it's ready
    std::promise<std::string> cake;
    std::future<std::string> cake_future = cake.get_future();
    std::thread microwave { bake_the_cake, std::move(cake) };

    while( cake_future.wait_for(0s) != std::future_status::ready) {
        std::cout << "laying the table.. wating for the bake..\n";
        std::this_thread::sleep_for(0.3s);
    }

    std::string cake_name = cake_future.get();
    std::cout << "Cake is ready. It's name is: " << cake_name << std::endl;

    microwave.join();
}

int main(int argc, char const *argv[])
{
    lay_the_table();

    return 0;
}
