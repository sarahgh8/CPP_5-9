#include "Bureaucrat.hpp"
using namespace std;

int main()
{
    try
    {
        Bureaucrat b1("Alice", 150);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        Bureaucrat b1("Alice", 151);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        Bureaucrat b1("Alice", 0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // test form
    return 0;
}