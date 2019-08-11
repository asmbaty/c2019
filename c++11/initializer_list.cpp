#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

struct vector3
{
	int x, y, z;

	vector3(int _x, int _y, int _z)
		: x(_x), y(_y), z(_z) {
	}

	vector3(const std::initializer_list<int>& list) {
		if (list.size() >= 3) {
			auto it = list.begin();
			x = *it++;
			y = *it++;
			z = *it++;
		}
		else {
			x = y = z = 0;
		}
	}

	void display() {
		std::cout << "(" << x << "," << y << "," << z << ")\n";
	}
};

int main()
{
	std::initializer_list<int> data = { 1,2,3,4 ,5 };

	std::vector<int> v{ 1,2,3,4,5 };

	std::vector<int>v2(data);

	vector3 x({ 1, 2, 3 }); // Automatically finds a contructor with 3 integer parameters if there is no one with initializer_list
	x.display();

	// Initialize a map with initializer_list
	std::map<std::string, int> m{
		{"yellow", 2},
		{"green", 3},
		{"blue", 4} };
	for (auto& entry : m)
		std::cout << entry.first << ' ' << entry.second << '\n';

	std::initializer_list<std::pair<const std::string, std::vector<int>>> map_list{
		{"primes", {2, 3, 5, 7}},
		{"odds", {1, 3, 5, 7, 9}} };

	std::map<std::string, std::vector<int>> sequences(map_list);

	return 0;
}