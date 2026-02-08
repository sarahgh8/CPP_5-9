#ifndef __SCALARCONVERTER_H__
#define __SCALARCONVERTER_H__

#include <iostream>
#include <string>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(ScalarConverter &o);
        ScalarConverter &operator=(ScalarConverter &o);
        ~ScalarConverter();
    public:
        static void convert(std::string str);

};

#endif