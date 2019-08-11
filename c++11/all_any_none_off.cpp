#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

bool is_prime(int n)
{
	for (int i = 2; i * i <= n; ++i)
		if (n % i == 0)
			return false;
	return true;
}

int main()
{
	std::vector<int> p{ 2, 3, 5, 7, 11, 13, 17, 19 };

	std::cout << "List { ";
	for (auto& i : p) std::cout << i << ' ';
	std::cout << "}" << std::endl;

	// std::all_of
	if (std::all_of(begin(p), end(p), is_prime)) {
		std::cout << "All numbers are primes\n";
	}

	// std::any_of
	if (std::any_of(begin(p), end(p), [](const int& i) {return i % 2 == 0; })) {

		std::cout << "There is an even number in the list\n";
	}

	// std::none_of
	if (std::none_of(begin(p), end(p), std::bind(std::greater<>(),
		std::placeholders::_1, 100))) {
		std::cout << "None of the list is greater than 100\n";
	}

	return 0;
}