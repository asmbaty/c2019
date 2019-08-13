// Struct Tag Type
#include <iostream>

struct doubler_t { explicit doubler_t() = default; } doubler;

class number_store
{
public:
    number_store(int num)
        : number(num)
    {}
    number_store(int num, doubler_t)
        : number(num*num)
    {}

    int get_value() const { return number; }
private:
    int number;
};

int main(int argc, char const *argv[])
{
    number_store v1(4);
    number_store v2(4, doubler);

    std::cout << v1.get_value() << std::endl;
    std::cout << v2.get_value() << std::endl;
    
    return 0;
}
