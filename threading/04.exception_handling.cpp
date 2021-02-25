// Threads: Exception Handling
#include <iostream>
#include <chrono>
#include <exception>
#include <thread>
using namespace std::chrono_literals;

[[noreturn]] void do_sensitive_job()
{
    std::cout << "workng hard on something low detailed..\n";
    std::cout << "oh no... an exception is thrown\n";
    throw std::runtime_error("sensitive exception thrown");
}

void heavy_calculations(std::exception_ptr& exp)
{
    // sensitive job may throw so we wrap it in a try-block
    try {
        do_sensitive_job();
    } catch(...) {
        std::cout << "heavy calculations encountered an exception\n";
        exp = std::current_exception();
    }
}

void run_thread()
{
    std::exception_ptr error;

    std::thread t1 { heavy_calculations, std::ref(error) };

    // wait for the thread to finish execution
    t1.join();

    // check for errors
    if(error != nullptr) { // error is a nullable pointer
        std::rethrow_exception(error);
    }
}

int main(int argc, char const *argv[])
{
    // catching an exception thrown in a different thread
    try {
        run_thread();
    } catch(const std::exception& e) {
        std::cout << "ERROR: " << e.what() << '\n';
    }

    return 0;
}
