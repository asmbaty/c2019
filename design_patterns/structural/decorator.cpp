// Decorator Design Pattern
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class shape
{
public:
	virtual std::string str() const = 0;
};

class circle : public shape
{
public:
	circle(int _radius) : radius(_radius) {}

	void resize(int new_radius)
	{
		radius = new_radius;
	}

	virtual std::string str() const override
	{
		std::ostringstream oss;
		oss << "A circle of radius " << radius;
		return oss.str();
	}
private:
	int radius;
};

class square : public shape
{
public:
	square(int _side) : side(_side) {}

	virtual std::string str() const override
	{
		std::ostringstream oss;
		oss << "A square with side " << side;
		return oss.str();
	}
private:
	int side;
};

// Dynamic decorator
class colored_shape : public shape
{
public:
	colored_shape(shape& _shape, const std::string& _color)
		: m_shape(_shape)
		, m_color(_color)
	{}

	virtual std::string str() const override
	{
		std::ostringstream oss;
		oss << m_shape.str() << " has the color " << m_color;
		return oss.str();
	}

private:
	shape& m_shape;
	std::string m_color;
};

// Dynamic decorator
class transparent_shape : public shape
{
public:
	transparent_shape(shape& _shape, uint8_t _transparency)
		: m_shape(_shape)
		, m_transparency(_transparency)
	{}

	virtual std::string str() const override
	{
		std::ostringstream oss;
		oss << m_shape.str() << " has " << static_cast<float>(m_transparency) / 255.f * 100.f << "% transparency";
		return oss.str();
	}

private:
	shape& m_shape;
	uint8_t m_transparency;
};

// Static decorator
template <typename T>
class static_colored_shape : public T
{
public:
	static_assert(std::is_base_of<shape, T>::value, "Template argument must be a shape");

	template <typename ...Args>
	static_colored_shape(const std::string& _color, Args ...args)
		: m_color(_color)
		, T(std::forward<Args>(args)...)
	{}

	virtual std::string str() const override
	{
		std::ostringstream oss;
		oss << T::str() << " has the color " << m_color;
		return oss.str();
	}

private:
	std::string m_color;
};

// Static decorator
template <typename T>
class static_transparent_shape : public T
{
public:
	static_assert(std::is_base_of<shape, T>::value, "Template argument must be a shape");

	template <typename ...Args>
	static_transparent_shape(uint8_t _transparency, Args ...args)
		: m_transparency(_transparency)
		, T(std::forward<Args>(args)...)
	{}

	virtual std::string str() const override
	{
		std::ostringstream oss;
		oss << T::str() << " has " << static_cast<float>(m_transparency) / 255.f * 100.f << "% transparency";
		return oss.str();
	}

private:
	uint8_t m_transparency;
};

int main()
{
	// dynamic decorator
	circle c{ 5 };
	colored_shape cs{ c, "yellow" };
	transparent_shape ts{ cs, 64 };
	std::cout << ts.str() << '\n';

	// static decorator
	static_transparent_shape<static_colored_shape<circle>> dc(101, "green", 4);
	dc.resize(8); // for dynamic decorator cricle class members are available cause ex
	std::cout << dc.str() << '\n';

	return 0;
}