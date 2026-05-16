#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <exception>

template <typename T>
class Array
{
    private:
        size_t s;
        T * data;
    public:
        Array(): s(0), data(NULL) {}

        Array(unsigned int n): s(n), data(NULL)
        {
            if (s > 0)
                data = new T[s];
        }

        Array(Array const &other): s(other.s), data(NULL)
        {
            if (s > 0)
            {
                data = new T[s];
                for (size_t i = 0; i < s; ++i)
                    data[i] = other.data[i];
            }
        }

        Array &operator=(Array const &other)
        {
            if (this != &other)
            {
                delete[] data;
                s = other.s;
                data = NULL;
                if (s > 0)
                {
                    data = new T[s];
                    for (size_t i = 0; i < s; ++i)
                        data[i] = other.data[i];
                }
            }
            return *this;
        }

        ~Array()
        {
            delete[] data;
        }

        T &operator[](size_t idx)
        {
            if (idx >= s)
                throw std::exception();
            return data[idx];
        }

        T const &operator[](size_t idx) const
        {
            if (idx >= s)
                throw std::exception();
            return data[idx];
        }

        size_t size() const { return s; }
};

#endif
