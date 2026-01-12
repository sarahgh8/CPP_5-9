#ifndef __FORM_HPP__
#define __FORM_HPP__

#include <string>
#include <exception>
#include <iostream>

class Form
{
    private:
        const std::string name;
        bool is_signed;
        const short grade_s;
        const short grade_e;
    
    class GradeTooHighException: public std::exception
    {

    };

    class GradeTooLowException: public std::exception
    {

    };

    public:
        Form();
        Form(const std::string &n, bool s, const short gs, const short ge);
        Form(const Form &o);
        Form &operator=(const Form &o);
        ~Form();
};

std::ostream &operator<<(std::ostream &out, Form &f);
#endif