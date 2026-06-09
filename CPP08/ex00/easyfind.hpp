#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <exception>
#include <algorithm>

template <typename T>
typename T::iterator easyfind(T &data, int find)
{
    return std::find(data.begin(), data.end(), find);
}

#endif
