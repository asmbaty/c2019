// Multiton Design Pattern
#include <iostream>
#include <memory>
#include <map>

enum class importance
{
	primary,
	secondary,
	tertiary // ['trshri]
};

// Limit the number of instances that can be instantiated
template<typename T, typename Key = std::string>
class Multiton
{
public:
	static std::shared_ptr<T> get(const Key& key)
	{
		if (auto it = instances.find(key); it != instances.end()) {
			return it->second;
		}
		auto instance = std::make_shared<T>();
		instances[key] = instance;
		return instance;
	}

private:
	static std::map<Key, std::shared_ptr<T>> instances;
};

template<typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances;

class printer
{
public:
	printer()
	{
		static int next_id = 1;
		id = next_id++;
	}

	int get_id() {
		return id;
	}

private:
	int id;
};

int main()
{
	typedef Multiton<printer, importance> PI;
	auto p1 = PI::get(importance::primary);
	auto p2 = PI::get(importance::primary);
	auto p3 = PI::get(importance::secondary);
	auto p4 = PI::get(importance::tertiary);
	auto p5 = PI::get(importance::tertiary);
	auto p6 = PI::get(importance::tertiary);

	std::cout << p1->get_id() << '\n';
	std::cout << p2->get_id() << '\n';
	std::cout << p3->get_id() << '\n';
	std::cout << p4->get_id() << '\n';
	std::cout << p5->get_id() << '\n';
	std::cout << p6->get_id() << '\n';

	return 0;
}