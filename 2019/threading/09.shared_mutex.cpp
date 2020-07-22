// Threads: Mutual Exclusions - Shared Mutex
#include <iostream>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <thread>
using namespace std::chrono_literals;

// multithreaded word writer
class word_writer
{
public:
    word_writer() = default;

    // obtains exclusive access
    void write(const std::string str)
    {
        std::unique_lock write_lock(m_mtx);
        m_text.push_back(' ');
        m_text += str;
    }

    // obtains shared access
    std::string last_written_word() const
    {
        std::shared_lock read_lock(m_mtx);
        size_t space = m_text.find_last_of(' ');
        if(space == std::string::npos) {
            return "";
        }
        return m_text.substr(space+1);
    }

    const std::string copy_full_text()const {
        std::shared_lock read_lock(m_mtx);
        return m_text;
    }

private:
    std::string m_text;
    mutable std::shared_mutex m_mtx;
};

int main(int argc, char const *argv[])
{
    word_writer ww;

    typedef std::initializer_list<std::string> word_set;   
    auto writer = [&ww](const word_set& w){
        for(auto& str : w) {
            ww.write(str);
            std::cout << ww.last_written_word() << '\n';
        }  
    };

    std::thread t1{writer, word_set{"one", "two", "three", "four", "five"} };
    std::thread t2{writer, word_set{"aaa", "bbb", "ccc", "ddd", "eee"} };
    std::thread t3{writer, word_set{"111", "222", "333", "444", "555"} };

    t1.join();
    t2.join();
    t3.join();

    std::cout << "..full text..\n";
    std::cout << ww.copy_full_text() << '\n';

    return 0;
}
