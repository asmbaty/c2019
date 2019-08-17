// Smart Pointers Aliasing
#include <iostream>
#include <memory>

int main(int argc, char const *argv[])
{
    std::shared_ptr<std::pair<int,int>> p(new std::pair<int,int>(1,2));
    std::shared_ptr<int> p1(p, &p->first);
    std::shared_ptr<int> p2(p, &p->second);

    std::cout << "use count: " << p1.use_count() << '\n';

    *p1 = 5;
    *p2 = 6;
    std::cout << p->first << ' ' << p->second << std::endl;
    p.reset();

    std::cout << "use count: " << p2.use_count() << '\n';

    return 0;
}