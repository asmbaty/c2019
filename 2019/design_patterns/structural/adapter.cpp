// Adapter
#include <iostream>
#include <memory>

// Renderer
class circle abstract
{
public:
	virtual void draw() const = 0;
};

class renderer
{
public:
	void render(const circle* c) { c->draw(); }
};

// say we have a different cicle implementation that doesn't inherit from the circle
class oa_circle
{
private:
	int radius;
public:
	oa_circle(int _radius) : radius(_radius) {}

	void oa_render()const
	{
		std::cout << "OA RENDER: " << radius << '\n';
	}
};

// create an adapter that adapts oa_circle to the circle
class circle_adapter : public circle, private oa_circle
{
public:
	circle_adapter(int _radius)
		: oa_circle(_radius)
	{}

	// Inherited via circle
	virtual void draw() const override
	{
		oa_circle::oa_render();
	}
};



int main_adapter_dp()
{
	std::unique_ptr<circle> f(new circle_adapter(4));
	renderer r;
	r.render(f.get());

	return 0;
}