#include <iostream>
#include <string>
#include <tuple>


int main()
{
	std::tuple<int, std::string> id(5, "Schwertize");
	std::tuple<float, std::string, unsigned int> bet(5.0f, "Maria", 4u);

	std::cout << std::get<0>(bet) << '\n';
	/*
	std::cout << std::get<4>(bet) << '\n'; // Compile rrror: Out of range
	std::string s = std::get<0>(bet); // Compire error: Wrong type cast
	int s = std::get<X>(bet); // Compire error: X must be a compile-time constant
	*/

	// Initialize with initializer_list
	std::tuple<int, int> cpp{ 1, 5 };

	// std::make_tuple()
	auto t = std::make_tuple(4, std::string{ "Ani" }, "Super", 'c');
	std::cout << typeid(t).name() << '\n';

	return 0;
}