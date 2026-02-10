#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include <iostream>
#include <stdint.h>

struct Data
{
    uintptr_t value;
};

class Serializer
{
    private:
        Serializer();
        ~Serializer();
        Serializer(Serializer &o);
        Serializer &operator=(Serializer &o);
    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};

#endif