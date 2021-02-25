// Bridge
#include <iostream>
#include <string>

class license abstract
{
public:
	virtual std::string get_rules() = 0;
};

class free_license : public license
{
public:
	virtual std::string get_rules() override
	{
		return std::string("You can freely use this product.");
	}
};

class paid_license : public license
{
public:
	virtual std::string get_rules() override
	{
		return std::string("You have to paid for the product.");
	}
};

class application
{
public:
	application(license& ll)
		: m_license(ll)
	{}

	virtual void print_license()
	{
		std::cout << m_license.get_rules() << '\n';
	}
protected:
	license& m_license;
};

class alarm_app : public application
{
public:
	alarm_app(license& ll)
		: application(ll)
	{}

	virtual void print_license()
	{
		std::cout << "Alarm App. " << m_license.get_rules() << '\n';
	}
};

class notes_app : public application
{
public:
	notes_app(license& ll)
		: application(ll)
	{}

	virtual void print_license()
	{
		std::cout << "Notes App. " << m_license.get_rules() << '\n';
	}
};


int main_bridge()
{
	free_license m_free_license;
	paid_license m_paid_license;

	notes_app notes(m_paid_license);
	notes.print_license();

	alarm_app alarm(m_free_license);
	alarm.print_license();

	return 0;
}