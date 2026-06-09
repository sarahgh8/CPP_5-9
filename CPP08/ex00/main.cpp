#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

template <typename T>
void print_result(T &container, int value)
{
    typename T::iterator it = easyfind(container, value);

    if (it == container.end())
    {
        std::cout << value << " not found" << std::endl;
        return;
    }
    std::cout << value << " found" << std::endl;
}

int main()
{
    std::vector<int> values;
    std::list<int> numbers;

    for (int i = 0; i < 5; ++i)
    {
        values.push_back(i * 10);
        numbers.push_back(i + 1);
    }

    values.push_back(20);
    numbers.push_back(3);

    print_result(values, 20);
    print_result(values, 7);
    print_result(numbers, 3);
    print_result(numbers, 42);
    return 0;
}