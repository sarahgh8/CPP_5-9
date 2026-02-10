#include "Serializer.hpp"

int main()
{
    Data d;

    d.value = 42;
    uintptr_t p = Serializer::serialize(&d);
    Data *n = Serializer::deserialize(p);

    std::cout << &d << std::endl;
    std::cout << n << std::endl;
    std::cout << p << std::endl;

    if((unsigned long)&d == p)
        std::cout << "yes\n";

    return 0;
}