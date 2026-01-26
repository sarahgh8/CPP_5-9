#ifndef __ROBOTOMYREQUESTFORM_HPP__
#define __ROBOTOMYREQUESTFORM_HPP__

#include <string>
#include <exception>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
    private:
        std::string target;

    public:
        RobotomyRequestForm(const std::string &t);
        RobotomyRequestForm(const RobotomyRequestForm &o);
        ~RobotomyRequestForm();
        RobotomyRequestForm &operator=(RobotomyRequestForm &o);

        void execute(Bureaucrat const &exec) const;
};

#endif