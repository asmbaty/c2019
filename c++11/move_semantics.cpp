#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

class bottle
{
private:
	static int count;
public:
	int id;
	double litres;
	std::string brandname;

	bottle(double l, std::string n)
		: litres(l)
		, brandname(n)
	{
		std::cout << "bottle: " << (id = ++count) << '\n';
	}

	bottle(bottle const& b)
		: litres(b.litres)
		, brandname(b.brandname)
	{
		std::cout << "copy bottle: " << (id = ++count) << '\n';
	}

	bottle(bottle && b) noexcept
		: litres(b.litres)
		, brandname(b.brandname)
	{
		std::cout << "move bottle: " << (id = ++count) << '\n';
	}

	bottle & operator = (bottle && b) noexcept
	{
		if (this != &b) {
			litres = b.litres;
			brandname = b.brandname;
			std::cout << "= bottle: " << (id = ++count) << '\n';
		}
		return *this;
	}

	~bottle() {
		std::cout << "bottle " << id << " destroyed\n";
	}
};

int bottle::count = 0;

bottle get_big_bottle()
{
	bottle b{ 0.5, "sil" };
	return b;
}

int get_next_number()
{
	static int i = 0;
	return ++i;
}


int non_main_move()
{
	// RVALUE REFERENCES
	int x = 6;
	int&& r = (x + 1);
	std::cout << r << '\n';

	// rvalue of user-defined type is mutable
	bottle b = get_big_bottle();
	std::cout << b.id << '\n';

	return 0;
}