// Threads: Complete Example
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <fstream>
#include <queue>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
using namespace std::chrono_literals;

// Multithreaded logger class
class logger
{
public:
    // Starts a background thread writing log entries to a file
    logger();

    // Terminate the thread on object's destruction
    virtual ~logger();

    // Prevent copy construction and assignment
    logger(logger const&) = delete;
    logger& operator=(logger const& ) = delete;

    // Add log entry to the queue
    void log(std::string entry);

private:
    // The method running in the background thread
    void process_entries();

    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cond_var;
    std::queue<std::string> m_queue;

    // A flag telling the background thread to terminate
    bool m_exit = false;
};

logger::logger()
{
    m_thread = std::thread{&logger::process_entries, this};
}

logger::~logger()
{
    {
        std::unique_lock lock(m_mutex);
        m_exit = true;

        // maybe the thread is waiting for a notification
        m_cond_var.notify_all();
    }
    m_thread.join();
}

void logger::log(std::string entry)
{
    std::unique_lock lock(m_mutex);
    m_queue.push(entry);
    m_cond_var.notify_all();
}

void logger::process_entries()
{
    std::ofstream log_file("log.txt");
    if(log_file.fail()) {
        std::cerr << "Failed to open logfile\n";
        return;
    }

    std::unique_lock lock(m_mutex);
    while(true) {
            if(!m_exit) {
                m_cond_var.wait(lock/*, [this](){return !m_queue.empty();}*/);
                // no pred required, in the destructor, the thread is forced to stop
            }
            lock.unlock();
            while(true) {
                lock.lock();
                if(m_queue.empty()) {
                    break;
                }
                log_file << m_queue.front() << std::endl;
                m_queue.pop();
                lock.unlock();
            }
            if(m_exit) {
                break;
            }
    }
}

void logSomeMessages(int id, logger& log)
{
    for (int i = 0; i < 10; ++i) {
        std::stringstream ss;
        ss << "Log entry " << i << " from thread " << id;
        log.log(ss.str());
    }
}
int main(int argc, char const *argv[])
{
    logger log;
    std::vector<std::thread> threads;
    // Create a few threads all working with the same Logger instance.
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(logSomeMessages, i, std::ref(log));
    }
    // Wait for all threads to finish.
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}