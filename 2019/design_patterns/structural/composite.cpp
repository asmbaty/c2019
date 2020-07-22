// Composite Design Pattern
#include <iostream>
#include <vector>
#include <string>

class component
{
public:
	virtual void who_am_i() = 0;
};

class primitive : public component
{
public:
	primitive(int _value) : value(_value) {}
	virtual void who_am_i() override
	{
		std::cout << "primitive: " << value << '\n';
	}
private:
	int value;
};

class composite : public component
{
public:
	composite() {}

	virtual void who_am_i() override
	{
		std::cout << "composite\n(";
		for (auto& v : vec) { std::cout << "\t"; v->who_am_i(); }
		std::cout << ")" << std::endl;
	}

	void add(component* c) { vec.push_back(c); }
private:
	std::vector<component*> vec;
};



int main_composite()
{
	composite p;
	p.add(new primitive{ 1 });
	p.add(new primitive{ 2 });
	p.add(new primitive{ 3 });

	composite p2;
	p2.add(new primitive{ 1 });
	p2.add(&p);
	p2.add(new primitive{ 2 });

	p2.who_am_i();


	return 0;
}