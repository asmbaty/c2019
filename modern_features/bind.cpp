#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

void add_up(int& a, int b)
{
	a += b;
}

int main()
{
	auto add_up_reversed = std::bind(&add_up, std::placeholders::_2, std::placeholders::_1);
	int x = 4, y = 6;
	add_up_reversed(x, y);
	std::cout << x << ' ' << y << '\n';

	std::function<void(int&)> add_by_5 = std::bind(&add_up, std::placeholders::_1, 5);
	x = 4, y = 6;
	add_by_5(x);
	std::cout << x << ' ' << y << '\n';
	std::cout << "---------------------------\n";

	std::vector<int> v = { 1,2,3,4,5 };
	std::for_each(begin(v), end(v), std::bind(&add_up, std::placeholders::_1, std::placeholders::_1));
	for (auto i : v) std::cout << i << '\n';

	return 0;
}