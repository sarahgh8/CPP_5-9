#ifndef __PRESIDENTIALPARDONFORM_HPP__
#define __PRESIDENTIALPARDONFORM_HPP__

#include <string>
#include <exception>
#include <iostream>
#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
    private:
        std::string target;

    public:
        PresidentialPardonForm(const std::string &t);
        PresidentialPardonForm(const PresidentialPardonForm &o);
        ~PresidentialPardonForm();
        PresidentialPardonForm &operator=(PresidentialPardonForm &o);

        void execute(Bureaucrat const &exec) const;
};

#endif