// Threads: Condition Variables
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
using namespace std::chrono_literals;

// COMPLICATED AND NOT VERIFIED

// background worker queue
class background_worker
{
public:
    background_worker()
    {
        // the foreground thread
        m_thread = std::thread{&background_worker::tracker, this};
        m_thread.detach();
    }

    void tracker()
    {
        auto there_is_a_task_to_execute = [this](){
            std::cout << "checking for an item..\n";
            return !m_tasks.empty();
        };

        // the background thread
        std::unique_lock lock(m_mutex);
        while(true) {
            m_condition.wait(lock, there_is_a_task_to_execute);
            auto task = m_tasks.front(); m_tasks.pop();
            
            std::cout << "Executing.. " << task << '\n';
            lock.unlock();
            std::this_thread::sleep_for(0.9s);
            ++m_done;
            lock.lock();
        }        
    }
    
    void add_task(const std::string task)
    {
        // the foreground thread
        std::unique_lock lock(m_mutex);
        m_tasks.push(task);
        m_condition.notify_all();
    }

    unsigned tasks_done() const { return m_done; }
    unsigned tasks_waiting() const { return m_tasks.size(); }

private:
    unsigned m_done = 0;
    std::queue<std::string> m_tasks;
    std::mutex m_mutex;
    std::thread m_thread; // bad idea ??
    std::condition_variable m_condition;
};

int main(int argc, char const *argv[])
{
    background_worker bw;

    // adding tasks for the background thread while working here
    for(int i=1;i<=10;++i) {
        std::cout << "step " << i << ", done: " << bw.tasks_done() 
                << ", waiting: " << bw.tasks_waiting() << std::endl;
        const std::string task = "task-" + std::to_string(i);
        std::cout << "adding: " << task << std::endl;
        bw.add_task(task);
        std::this_thread::sleep_for(0.5s);
    }

    std::cout << "-------------finished adding tasks--------------\n";

    while (bw.tasks_waiting())
    {
        std::cout << "waiting to finish.. done: " << bw.tasks_done() 
                << ", waiting: " << bw.tasks_waiting() << std::endl;
        std::this_thread::sleep_for(0.5s);
    }

    return 0;
}
