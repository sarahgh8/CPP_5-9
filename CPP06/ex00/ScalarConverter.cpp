#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(ScalarConverter &o)
{
    std::cout << "Copy constructor\n";
}
ScalarConverter &ScalarConverter::operator=(ScalarConverter &o)
{
    std::cout << "Assignment operator constructor\n";
}

ScalarConverter::~ScalarConverter()
{
    std::cout << "Destructor\n";
}

int is_float_double(std::string s)
{
    int i = 0;
    bool dot = false;
    while(s[i + 1])
    {
        if(s[i] == '.')
            dot = true;
        if(!isdigit(s[i]) && s[i] != '.')
            return 0;
        i++;
    }
    if(s[i] == 'f' && dot)
        return 1;
    else if(dot)
        return 2;
    return 0;
}

char getStrType(std::string s)
{

    if((s[0] >= 65 && s[0] <= 90) || (s[0] >= 97 && s[0] <= 122))
        return 'c';
    else if(is_float_double(s) == 1)
        return 'f';
    else if(is_float_double(s) == 2)
        return 'd';
    else
        return 'i';
}

void convert(std::string str)
{
    if(str[0] == '0')
    {
        std::cout << "char: Non displayable\n";
        std::cout << "int: 0\n";
        std::cout << "float: 0.0f\n";
        std::cout << "double: 0.0\n";
    }
    else if(str == "nan")
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: nanf\n";
        std::cout << "double: nan\n";
    }
    else
    {
        char type = getStrType(str);
        if(type == 'c')
        {
            char c = str[0];
            convert_char()
        }
        else if (type == 'i')
            int i = std::stoi(str);
        else if(type == 'f')
            float f = std::strtof(str.c_str(), nullptr);
        else if(type == 'd')
            double d = std::stod(str);
    }
}
