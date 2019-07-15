#pragma once
#include <queue>
#include <memory>
#include <iostream>

class resource
{
private:
	int value;
	int id;
public:
	resource(int _value = 0) : value(_value) { static int x = 0; std::cout << "created " << (id = ++x) << '\n'; }
	~resource() { std::cout << "destroyed " << id << "\n"; }

	virtual void reset() { value = 0; }
	void set_value(int _value) { value = _value; }
	int get_value() { return value; }

	resource(resource const&) = delete;
	resource& operator = (resource const &) = delete;
	
	resource(resource&& other) noexcept
		: value(other.value)
		, id(other.id)
	{
		std::cout << "move ctor " << id << "\n";
	}
	resource& operator = (resource&& other) noexcept
	{
		std::cout << "operator = && " << id << "\n";
		if (this != &other) {
			this->value = other.value;
			this->id = other.id;
		}
	}

};

class ObjectPool
{
public:
	typedef std::unique_ptr<resource> ptr;
private:
	std::queue<ptr> resources;

public:
	ObjectPool() {}

	ptr acquire()
	{
		if (!resources.empty()) {
			auto inst = std::move(resources.front());
			resources.pop();
			return std::move(inst);
		}
		return ptr(new resource());
	}

	void release(ptr p) { resources.push(std::move(p)); }

	void clear() { while (!resources.empty()) resources.pop(); }
};

class object_pool_use
{
public:
	static void use()
	{
		ObjectPool pool;
		auto obj1 = pool.acquire();
		obj1->set_value(1);
		std::cout << obj1->get_value() << '\n';
		pool.release(std::move(obj1)); // There is an error here 
		auto obj2 = pool.acquire();
		std::cout << obj1->get_value() << '\n';

		std::cout << "end of use\n";
	}
};