#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Test 1: Intern creates robotomy request ===" << std::endl;
    try
    {
        Intern someRandomIntern;
        AForm* rrf;
        
        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        
        Bureaucrat bob("Bob", 1);
        std::cout << *rrf << std::endl;
        bob.signForm(*rrf);
        bob.executeForm(*rrf);
        
        delete rrf;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 2: Intern creates shrubbery creation ===" << std::endl;
    try
    {
        Intern intern;
        AForm* form;
        
        form = intern.makeForm("shrubbery creation", "home");
        
        Bureaucrat alice("Alice", 1);
        std::cout << *form << std::endl;
        alice.signForm(*form);
        alice.executeForm(*form);
        
        delete form;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 3: Intern creates presidential pardon ===" << std::endl;
    try
    {
        Intern intern;
        AForm* form;
        
        form = intern.makeForm("presidential pardon", "Arthur Dent");
        
        Bureaucrat president("President", 1);
        std::cout << *form << std::endl;
        president.signForm(*form);
        president.executeForm(*form);
        
        delete form;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 4: Intern tries to create invalid form ===" << std::endl;
    try
    {
        Intern intern;
        AForm* form;
        
        form = intern.makeForm("invalid form", "target");
        
        if (form == NULL)
            std::cout << "Form creation failed as expected" << std::endl;
        else
        {
            std::cout << *form << std::endl;
            delete form;
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 5: Multiple forms created by same intern ===" << std::endl;
    try
    {
        Intern intern;
        Bureaucrat boss("Boss", 1);
        
        AForm* form1 = intern.makeForm("robotomy request", "Target1");
        AForm* form2 = intern.makeForm("shrubbery creation", "garden");
        AForm* form3 = intern.makeForm("presidential pardon", "Criminal");
        
        boss.signForm(*form1);
        boss.signForm(*form2);
        boss.signForm(*form3);
        
        boss.executeForm(*form1);
        boss.executeForm(*form2);
        boss.executeForm(*form3);
        
        delete form1;
        delete form2;
        delete form3;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}