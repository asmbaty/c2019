// Threads: Mutual Exclusions - Timed Mutex
#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
using namespace std::chrono_literals;

class counter
{
public:
    counter(int id, int num_iterations)
        : m_id(id)
        , m_num_iterations(num_iterations)
    {}
    void operator () ()
    {
        for(int i=1; i<=m_num_iterations; ++i) {
            // timed mutex waits for 0.2s to gain access
            // the operation takes 0.1s so many locks are going to be missed
            std::unique_lock lock(m_mutex, 0.2s);
            if(lock) {
                std::cout << "thread: " << m_id << ", iteration: " << i << '\n';
                std::this_thread::sleep_for(0.1s);
            }
        }
    } 
private:
    int m_id;
    int m_num_iterations;
    static std::timed_mutex m_mutex;
};

std::timed_mutex counter::m_mutex;

int main(int argc, char const *argv[])
{
    std::vector<counter> counters;
    std::vector<std::thread> threads;
    for(int i=1;i<=5;++i) {
        const counter& c = counters.emplace_back(counter{i,5});
        threads.push_back(std::thread{ c });
    }

    for(auto& t : threads) {
        t.join();
    }

    return 0;
}
