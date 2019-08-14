// Threads Local Storage
#include <iostream>
#include <chrono>
#include <functional>
#include <string>
#include <thread>
using namespace std::chrono_literals;

class hello_goodbye
{
public:
    hello_goodbye() { std::cout << "hello!" << std::endl;}
    ~hello_goodbye() { std::cout << "goodbye!" << std::endl;}
    void hi(const std::string& name) { std::cout << "hi " << name << '!' << std::endl;}
};

thread_local hello_goodbye hi_bye;
thread_local std::string thread_name = "no name\n";

int main(int argc, char const *argv[])
{
    std::thread t1 { []{
        std::this_thread::sleep_for(0.1s);
        thread_name = "first thread";
        hi_bye.hi(thread_name);
        for(int i=0;i<10;++i) {
            std::cout << "thread name: " << thread_name << std::endl;
            std::this_thread::sleep_for(0.7s);
        }
    } };

    std::thread t2 { []{
        std::this_thread::sleep_for(0.2s);
        thread_name = "second thread";
        hi_bye.hi(thread_name);
        for(int i=0;i<10;++i) {
            std::cout << "thread name: " << thread_name << std::endl;
            std::this_thread::sleep_for(0.9s);
        }
    } };

    t1.join();
    t2.join();

    std::cout << "anyway what was the thread name?: " << thread_name << '\n'; // no name

    return 0;
}
