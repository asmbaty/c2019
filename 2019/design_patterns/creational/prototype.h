#pragma once
#include <string>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <list>

class bullet abstract // interface 
{
private:
	int speed;
public:
	bullet(int _speed) : speed(_speed) {}
	virtual std::unique_ptr<bullet> clone() = 0;
	void fire() { std::cout << "Fire at the speed of " << speed << '\n'; }
};

class simple_bullet : public bullet
{
public:
	simple_bullet(int _speed) : bullet(_speed) {}
	// Inherited via bullet
	virtual std::unique_ptr<bullet> clone() override
	{
		return std::make_unique<simple_bullet>(*this);
	}
};

class double_bullet : public bullet
{
public:
	double_bullet(int _speed) : bullet(2 * _speed) {}
	// Inherited via bullet
	virtual std::unique_ptr<bullet> clone() override
	{
		return std::make_unique<double_bullet>(*this);
	}
};

class bullet_factory
{
public:
	enum class bullet_type
	{
		weak,
		good,
		strong,
		super
	};

private:
	std::unordered_map<bullet_type, std::unique_ptr<bullet>> m_bullets;

public:
	bullet_factory()
	{
		m_bullets[bullet_type::weak] = std::make_unique<simple_bullet>(10);
		m_bullets[bullet_type::good] = std::make_unique<simple_bullet>(20);
		m_bullets[bullet_type::strong] = std::make_unique<double_bullet>(30);
		m_bullets[bullet_type::super] = std::make_unique<double_bullet>(40);



	}

	std::unique_ptr<bullet> create(bullet_type t)
	{
		return m_bullets[t]->clone();
	}
};

class use_prototype
{
public:
	static void use()
	{
		bullet_factory factory;
		std::list<std::unique_ptr<bullet>> list;
		list.push_back(factory.create(bullet_factory::bullet_type::weak));
		list.push_back(factory.create(bullet_factory::bullet_type::good));
		list.push_back(factory.create(bullet_factory::bullet_type::strong));
		list.push_back(factory.create(bullet_factory::bullet_type::super));
		for (auto& u : list) { u->fire(); }


	}
};