#ifndef __FORM_HPP__
#define __FORM_HPP__

#include <string>
#include <exception>
#include <iostream>
#include "Bureaucrat.hpp"

class Form 
{
    private:
        const std::string name;
        bool is_signed;
        const short grade_s;
        const short grade_e;
    
    class GradeTooHighException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return "Grade too high\n";
            }
    };

    class GradeTooLowException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return "Grade too Low\n";
            }
    };

    public:
        Form();
        Form(const std::string &n, const short gs, const short ge);
        Form(const Form &o);
        Form &operator=(const Form &o);
        ~Form();
        
        const std::string &getName() const;
        bool getSigned() const;
        short getGradeToSign() const;
        short getGradeToExecute() const;
        
        void beSigned(Bureaucrat &o);
};

std::ostream &operator<<(std::ostream &out, const Form &f);
#endif