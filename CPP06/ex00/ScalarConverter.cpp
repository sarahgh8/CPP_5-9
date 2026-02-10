#include "ScalarConverter.hpp"
#include <limits>
#include <cmath>
#include <iomanip>

int is_float_double(std::string s)
{
    int i = 0;
    bool dot = false;
    
    if(s[i] == '-' || s[i] == '+')
        i++;
    
    if(!s[i])
        return 0;
    
    while(s[i + 1])
    {
        if(s[i] == '.')
            dot = true;
        else if(!isdigit(s[i]))
            return 0;
        i++;
    }
    if(s[i] == 'f' && dot)
        return 1;
    else if(dot && isdigit(s[i]))
        return 2;
    return 0;
}

char getStrType(std::string s)
{
    if(((s[0] >= 65 && s[0] <= 90) || (s[0] >= 97 && s[0] <= 122))
        && s.length() == 1)
        return 'c';
    else if(is_float_double(s) == 1)
        return 'f';
    else if(is_float_double(s) == 2)
        return 'd';
    else
        return 'i';
}

void convert_char(char c)
{
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast <int> (c) << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast <float> (c) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast <double> (c) << std::endl;
}

void convert_int(int i)
{
    if(i < 0 || i > 127)
        std::cout << "char: impossible" << std::endl;
    else if(i < 32 || i == 127)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast <char> (i) << "'" << std::endl;
    std::cout << "int: " << i << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast <float> (i) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast <double> (i) << std::endl;
}

void convert_float(float f)
{
    if(std::isnan(f) || std::isinf(f) || f < 0 || f > 127)
        std::cout << "char: impossible" << std::endl;
    else if(f < 32 || f >= 127)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast <char> (f) << "'" << std::endl;
    
    if(std::isnan(f) || std::isinf(f) || f < std::numeric_limits<int>::min() || f > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast <int> (f) << std::endl;
    
    std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast <double> (f) << std::endl;
}

void convert_double(double d)
{
    if(std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
        std::cout << "char: impossible" << std::endl;
    else if(d < 32 || d >= 127)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast <char> (d) << "'" << std::endl;
    
    if(std::isnan(d) || std::isinf(d) || d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast <int> (d) << std::endl;
    
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast <float> (d) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}

int isPsuedoLiteral(std::string str)
{
    if(str == "-inff" || str == "+inff" || str == "nanf"
        || str == "-inf" || str == "+inf" || str == "nan")
        return 1;
    return 0;
}

void ScalarConverter::convert(std::string str)
{
    if(isPsuedoLiteral(str))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        
        if(str == "nanf" || str == "nan")
        {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        }
        else if(str == "+inff" || str == "+inf")
        {
            std::cout << "float: +inff" << std::endl;
            std::cout << "double: +inf" << std::endl;
        }
        else if(str == "-inff" || str == "-inf")
        {
            std::cout << "float: -inff" << std::endl;
            std::cout << "double: -inf" << std::endl;
        }
    }
    else
    {
        char type = getStrType(str);
        if(type == 'c')
        {
            char c = str[0];
            convert_char(c);
        }
        else if (type == 'i')
        {
            int i = atoi(str.c_str());
            convert_int(i);
        }
        else if(type == 'f')
        {
            float f = atof(str.c_str());
            convert_float(f);
        }
        else if(type == 'd')
        {
            double d = atof(str.c_str());
            convert_double(d);
        }
    }
}
