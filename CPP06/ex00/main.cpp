#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
    if(argc == 2)
        ScalarConverter::convert(std::string(argv[1]));
    return 0;
}
