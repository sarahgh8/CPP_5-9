#ifndef __INTERN_H__
#define __INTERN_H__

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
    private:
        static AForm* createShrubberyForm(std::string target);
        static AForm* createRobotomyForm(std::string target);
        static AForm* createPresidentialForm(std::string target);
    public:
        Intern();
        ~Intern();
        Intern(const Intern &o);
        Intern &operator=(const Intern &o);
        AForm *makeForm(std::string Fname, std::string target);
};  

#endif