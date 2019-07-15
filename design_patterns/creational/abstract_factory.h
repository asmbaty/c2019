#pragma once
#include <iostream>

class tire abstract {
public:
	virtual void what() = 0;
};
class mersedes_tire : public tire {
public:
	virtual void what() override { std::cout << "mersedes tire\n"; }
};
class bmw_tire : public tire {
public:
	virtual void what() override { std::cout << "bmw tire\n"; }
};

class logo abstract {
public:
	virtual void what() = 0;
};
class mersedes_logo : public logo {
public:
	virtual void what() override { std::cout << "mersedes logo\n"; }
};
class bmw_logo : public logo {
public:
	virtual void what() override { std::cout << "bmw logo\n"; }
};

class car_factory abstract
{
public:
	virtual tire* create_tire() = 0;
	virtual logo* create_logo() = 0;
};

class mersedes_car_factory : public car_factory
{
public:
	virtual tire* create_tire() override { return new mersedes_tire; }
	virtual logo* create_logo() override { return new mersedes_logo; }
};

class bmw_car_factory : public car_factory
{
public:
	virtual tire* create_tire() override { return new bmw_tire; }
	virtual logo* create_logo() override { return new bmw_logo; }
};

enum class car_type {
	mersedes,
	bmw
};

class car_factory_usage
{
public:
	static void use(car_type type)
	{
		car_factory* f = nullptr;
		if(type == car_type::mersedes)
			f = new mersedes_car_factory();
		else
			f = new bmw_car_factory();
		tire* t = f->create_tire();
		logo* l = f->create_logo();
		t->what();
		l->what();
	}
};