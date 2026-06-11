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
template <typename T>
void print_cont(const T &cont)
{
    typename T::const_iterator it = cont.begin();
    typename T::const_iterator end = cont.end();

    for (; it != end; ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;
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

    std::cout << "values:"; 
    print_cont(values);
    std::cout << std::endl;
    std::cout << "numbers:"; 
    print_cont(numbers);
    std::cout << std::endl;

    values.push_back(20);
    numbers.push_back(3);

    print_result(values, 20);
    print_result(values, 7);
    print_result(numbers, 3);
    print_result(numbers, 42);
    return 0;
}