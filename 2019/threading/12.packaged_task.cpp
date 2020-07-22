// Threads: Futures - Packaged Task
#include <iostream>
#include <chrono>
#include <future>
#include <string>
#include <thread>
using namespace std::chrono_literals;

int divide(int x, int y) {
    // This is a long division process..
    std::this_thread::sleep_for(3s);
    if(y == 0) {
        throw std::runtime_error("divide by zero");
    }
    return x/y;
}

void handle_result(const std::string message, std::future<int>& result)
{
    try {   
        std::cout << message << ": " << result.get() << '\n';
    } catch(const std::exception& e) {
        std::cout << "exception: " << e.what() << '\n'; 
    }
}

void run_sync_example()
{
    std::packaged_task<int(int,int)> dtask(divide);
    std::future<int> result = dtask.get_future();

    dtask(8,2);
    handle_result("Sync 8/2", result);

}

void run_async_example()
{
    // Define two tasks
    std::packaged_task<int(int,int)> dtask1(divide);
    std::future<int> result1 = dtask1.get_future();

    std::packaged_task<int(int,int)> dtask2(divide);
    std::future<int> result2 = dtask2.get_future();

    std::thread t1{ std::move(dtask1), 9, 3 };
    std::thread t2{ std::move(dtask2), 4, 0 };

    // threads are running to calculate division values
    // while we wait here lets call the one wihch is not async
    run_sync_example();

    handle_result("Async 9/3", result1);
    handle_result("Async 4/0", result2);

    t1.join();
    t2.join();

} 

int main(int argc, char const *argv[])
{
    run_async_example();

    return 0;
}
