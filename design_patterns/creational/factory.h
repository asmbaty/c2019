#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

// Factory desing pattern
class enemy abstract
{
public:
	virtual void attack() = 0;

	// Factory Method
	static enemy* instantiate(char);

	virtual ~enemy() { std::cout << "Remove enemy base\n"; }
};

class ship_enemy : public enemy
{
public:
	virtual void attack() override final {
		std::cout << "ship attacks\n";
	}

	~ship_enemy() { std::cout << "Remove base enemy\n"; }
};

class big_boss_enemy : public enemy
{
public:
	virtual void attack() override final {
		std::cout << "big boss attack\n";
	}

	~big_boss_enemy() { std::cout << "Remove big boss enemy\n"; }
};

class soldier_enemy : public enemy
{
public:
	virtual void attack() override final {
		std::cout << "soldier attack\n";
	}

	~soldier_enemy() { std::cout << "Remove soldier enemy\n"; }
};

enemy* enemy::instantiate(char c)
{
	switch (c)
	{
	case 's':
		return new soldier_enemy;
	case 'c':
		return new ship_enemy;
	case 'b':
		return new big_boss_enemy;
	}
	return nullptr;
}
class factory_example
{
public:
	void use() {
		std::vector<enemy*> enemies;
		enemies.push_back(enemy::instantiate('c'));
		enemies.push_back(enemy::instantiate('b'));
		enemies.push_back(enemy::instantiate('s'));
		std::for_each(begin(enemies), end(enemies), [](auto & x) {x->attack(); delete x; });
	}
};