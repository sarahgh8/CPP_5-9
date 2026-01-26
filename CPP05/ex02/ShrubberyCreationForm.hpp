#ifndef __SHRUBBERYCREATIONFORM_HPP__
#define __SHRUBBERYCREATIONFORM_HPP__

#include "AForm.hpp"
#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>

class ShrubberyCreationForm : public AForm
{
    private:
        std::string target;

    public:
        ShrubberyCreationForm(const std::string &t);
        ShrubberyCreationForm(const ShrubberyCreationForm &o);
        ~ShrubberyCreationForm();
        ShrubberyCreationForm &operator=(ShrubberyCreationForm &o);

        void execute(Bureaucrat const &exec) const;

        class ExceptionNotSigned : public std::exception
        {
            const char *what() const throw()
            {
                return "Form is not signed\n";
            }
        };

        class ExceptionFileIsNotOpen : public std::exception
        {
            const char *what() const throw()
            {
                return "File could not open\n";
            }
        };

        
};

#endif