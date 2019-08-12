// Threads with Function Objects (Functors)
#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
using namespace std::chrono_literals;

class iterate_hello
{
public:
    iterate_hello(int id, int num_iterations)
        : m_id(id)
        , m_count(num_iterations)
    {}

    void operator() ()
    {

        for(int i=1; i<=m_count; ++i) {
            std::cout << "Hello from " << m_id << ": " << i << " times" << std::endl;
            std::this_thread::sleep_for(0.1s);
        }
    }
private:
    int m_id;
    int m_count;
};

int main(int argc, char const *argv[])
{
    iterate_hello i1{1, 5}, i2{2,6}, i3{3,7};

    std::thread t1{ std::ref(i1) };
    std::thread t2{ std::ref(i2) };
    std::thread t3{ std::ref(i3) };

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
