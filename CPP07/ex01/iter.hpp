#ifndef __ITER_HPP__
#define __ITER_HPP__

#include <iostream>
#include <string>

template <typename T>
void iter(T *array, const size_t length, void (*f)(T &))
{
	for (unsigned int i = 0; i < length; ++i)
		f(array[i]);
}

template <typename T>
void iter(const T *array, const size_t length, void (*f)(const T &))
{
	for (unsigned int i = 0; i < length; ++i)
		f(array[i]);
}

template <typename T>
void print(T &value)
{
	std::cout << value << std::endl;
}

template <typename T>
void byTwo(T &value)
{
	value *= 2;
}

template <typename T>
void print_const(const T &value)
{
	std::cout << value << std::endl;
}

#endif
