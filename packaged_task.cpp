#include <iostream>
#include <future> // packaged_task
#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char const *argv[])
{
    // a callable target (function, lambda expression, bind expression, a function object)
    // The class template std::packaged_task wraps any Callable target so that it can be invoked asynchronously.
    // Its return value or exception thrown is stored in a shared state which can be accessed through std::future object.

    std::packaged_task<int(int,int)> long_sum ( [](int a, int b) -> int {
        std::this_thread::sleep_for(3s);
        throw std::runtime_error("sum thrown an exception");
        return a+b;
    });

    std::cout << "long_sum executing..\n";

    std::future<int> result = long_sum.get_future();
    std::jthread long_task(std::move(long_sum), 7, 8);

    std::cout << "long_sum executed!\n";

    try {
        std::cout << result.get() << '\n';
    } catch(std::exception& e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}
