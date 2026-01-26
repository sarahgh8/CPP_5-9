#include "Intern.hpp"

Intern::Intern()
{
    std::cout << "Intern: Default constructor\n";
}
Intern::~Intern()
{
    std::cout << "Intern: Destructor\n";
}
Intern::Intern(const Intern &o)
{
    std::cout << "Intern: Copy constructor\n";
    (void)o;
}
Intern &Intern::operator=(const Intern &o)
{
    std::cout << "Intern: Assignment Operator\n";
    (void)o;
    return *this;
}

AForm* Intern::createShrubberyForm(std::string target)
{
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyForm(std::string target)
{
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialForm(std::string target)
{
    return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string Fname, std::string target)
{
    std::string formNames[] = {"shrubbery creation", "robotomy request", "presidential pardon"};
    AForm* (*formCreators[])(std::string) = {&createShrubberyForm, &createRobotomyForm, &createPresidentialForm};
    
    for(int i = 0; i < 3; i++)
    {
        if(Fname == formNames[i])
        {
            std::cout << "Intern creates " << Fname << std::endl;
            return formCreators[i](target);
        }
    }
    std::cout << "Error: Form name \"" << Fname << "\" does not exist" << std::endl;
    return NULL;
}