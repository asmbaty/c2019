#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

class bigA {
public:
	bigA() { std::cout << "Big A object created\n"; }
	bigA(bigA const&) { std::cout << "bigA object copied\n"; }
	void print() { std::cout << "print me: " << this << '\n'; }
};

// A method returning a pow function for any type and number
template<class T>
std::function<T(T)> get_power_function(int n)
{
	return [n](T x) mutable {T result = T(1); while (n-- != 0) result *= x; return result; };
}

class odd_counter
{
	unsigned int m_counter = 0;

public:
	unsigned int get_count()const { return m_counter; }

	void count(const std::vector<int>& v)
	{
		std::for_each(begin(v), end(v), [this](auto & x) {m_counter += x & 1; });
	}
};

int main()
{
	std::vector<int> v{ 1,2,3,4,5 };
	std::for_each(begin(v), end(v), [](auto & x) {x *= x; });
	std::for_each(begin(v), end(v), [](auto & x) {std::cout << x << ','; });

	int sum = 0;
	std::for_each(begin(v), end(v), [&sum](auto & x) {sum += x; });
	std::cout << "sum: " << sum << '\n';

	bigA b;
	std::for_each(begin(v), end(v), [b](auto & x) mutable { b.print(); });

	// Return functions
	auto power_of_2 = get_power_function<int>(2);
	auto power_of_3 = get_power_function<unsigned>(3);

	std::cout << "5 power 2 is " << power_of_2(5) << '\n';
	std::cout << "5 power 3 is " << power_of_3(5u) << '\n';

	odd_counter cc;
	cc.count(v);
	std::cout << "number of odds in the vector: " << cc.get_count() << '\n';

	return 0;
}