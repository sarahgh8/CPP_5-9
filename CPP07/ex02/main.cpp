#include <iostream>
#include "Array.hpp"

int main()
{
    Array<int> empty;
    std::cout << "empty size: " << empty.size() << std::endl;

    Array<int> a(5);
    for (size_t i = 0; i < a.size(); ++i)
        a[i] = static_cast<int>(i + 1);

    Array<int> b(a);
    a[0] = 42;

    std::cout << "a[0]=" << a[0] << " b[0]=" << b[0] << std::endl;

    Array<int> c;
    c = b;
    c[1] = 99;
    std::cout << "b[1]=" << b[1] << " c[1]=" << c[1] << std::endl;

    try
    {
        std::cout << a[10] << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "caught exception on out-of-bounds access" << std::endl;
    }

    return 0;
}
