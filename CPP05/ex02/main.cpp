#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Test 1: ShrubberyCreationForm ===" << std::endl;
    try
    {
        Bureaucrat bob("Bob", 130);
        ShrubberyCreationForm shrub("home");
        
        std::cout << bob << std::endl;
        std::cout << shrub << std::endl;
        
        bob.signForm(shrub);
        bob.executeForm(shrub);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 2: ShrubberyCreationForm - Grade too low to sign ===" << std::endl;
    try
    {
        Bureaucrat alice("Alice", 150);
        ShrubberyCreationForm shrub("garden");
        
        std::cout << alice << std::endl;
        alice.signForm(shrub);
        alice.executeForm(shrub);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 3: RobotomyRequestForm ===" << std::endl;
    try
    {
        Bureaucrat charlie("Charlie", 40);
        RobotomyRequestForm robot("Bender");
        
        std::cout << charlie << std::endl;
        std::cout << robot << std::endl;
        
        charlie.signForm(robot);
        charlie.executeForm(robot);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 4: RobotomyRequestForm - Execute without signing ===" << std::endl;
    try
    {
        Bureaucrat dave("Dave", 1);
        RobotomyRequestForm robot("Target");
        
        dave.executeForm(robot);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 5: PresidentialPardonForm ===" << std::endl;
    try
    {
        Bureaucrat president("President", 1);
        PresidentialPardonForm pardon("Arthur Dent");
        
        std::cout << president << std::endl;
        std::cout << pardon << std::endl;
        
        president.signForm(pardon);
        president.executeForm(pardon);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 6: PresidentialPardonForm - Grade too low to execute ===" << std::endl;
    try
    {
        Bureaucrat lowGrade("LowGrade", 20);
        Bureaucrat highGrade("HighGrade", 1);
        PresidentialPardonForm pardon("Ford Prefect");
        
        highGrade.signForm(pardon);
        lowGrade.executeForm(pardon);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Test 7: Multiple forms with same bureaucrat ===" << std::endl;
    try
    {
        Bureaucrat superBureaucrat("SuperBureaucrat", 1);
        ShrubberyCreationForm shrub("office");
        RobotomyRequestForm robot("Employee");
        PresidentialPardonForm pardon("Criminal");
        
        std::cout << superBureaucrat << std::endl;
        
        superBureaucrat.signForm(shrub);
        superBureaucrat.signForm(robot);
        superBureaucrat.signForm(pardon);
        
        superBureaucrat.executeForm(shrub);
        superBureaucrat.executeForm(robot);
        superBureaucrat.executeForm(pardon);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}