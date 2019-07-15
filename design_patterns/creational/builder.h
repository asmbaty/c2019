#pragma once
#include <string>
#include <iostream>

struct car
{
	std::string name;
	int speed;
	std::string color;

	void print_specifications()
	{
		std::cout << color << ' ' << name << ", speed: " << speed << " mph\n";
	}
};

class car_builder abstract
{
public:
	virtual std::string give_name() = 0;
	virtual int test_speed() = 0;
	virtual std::string paint() = 0;
};

class mechanic // director
{
public:
	void set_builder(car_builder* cb)
	{
		builder = cb;
	}

	car* build_car()
	{
		return new car{ 
			builder->give_name(),
			builder->test_speed(),
			builder->paint() };
	}

private:
	car_builder* builder;
};

class armenian_tuning : public car_builder
{
public:
	virtual std::string give_name() override { return "Brabus"; }
	virtual int test_speed() override { return 180; }
	virtual std::string paint() override { return "Black"; }
};

class swiss_tuning : public car_builder
{
public:
	virtual std::string give_name() override { return "Ferrary"; }
	virtual int test_speed() override { return 360; }
	virtual std::string paint() override { return "Yellow"; }
};

class builder_example_class
{
public:
	static void use()
	{
		mechanic m;
		armenian_tuning arm_tune;
		swiss_tuning sws_tune;

		m.set_builder(&arm_tune);
		auto armenian_car = m.build_car();

		m.set_builder(&sws_tune);
		auto swiss_car = m.build_car();

		armenian_car->print_specifications();
		swiss_car->print_specifications();

		delete armenian_car;
		delete swiss_car;
	}
};