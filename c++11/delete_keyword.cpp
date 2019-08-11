#include <iostream>
#include <string>

class user
{
public:
	user(unsigned int userId, std::string userName)
		: id(userId)
		, name(userName)
	{}

	// Delete the copy constructor
	user(user const&) = delete;

	// Delete the assignment operator
	user& operator = (user const&) = delete;

	// Delete other constructors that would be accepted by default
	user(float, std::string) = delete;
	user(int, std::string) = delete;

	// Restrict object creation on heap by deleting the new operator
	void* operator new (size_t) = delete;

private:
	unsigned int id;
	std::string name;

};

// Remove a template specialization
template<class T>
class some_class
{
	T x, y;
public:
	some_class(T a, T b) : x(a), y(b) {}

	some_class(double, double) = delete;
};

int main()
{
	user u(1u, "Aharon");

	return 0;
}