#pragma once
#include <thread>
#include <mutex>
#include <memory>

// Thread-safe singleton class ???
class singleton
{
private:
	int m_value;

	singleton()
		: m_value(0)
	{}

	static singleton* m_instance;
	static std::mutex mtx;

public:
	static singleton* get_instance()
	{
		if (m_instance == nullptr) {
			mtx.lock();
			if (m_instance == nullptr) {
				m_instance = new singleton();
			}
			mtx.unlock();
		}
		return m_instance;
	}

	~singleton() {}
};

singleton *singleton::m_instance = nullptr;
std::mutex singleton::mtx;


class singleton2
{
public:
	singleton2(singleton2 const&) = delete;
	void operator = (singleton2 const&) = delete;

	static std::shared_ptr<singleton2> get_instance()
	{
		static std::shared_ptr<singleton2> s{new singleton2};
		return s;
	}

private:
	singleton2() { std::cout << "Create the singleton object\n"; }
};