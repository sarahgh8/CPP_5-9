#ifndef __AFORM_HPP__
#define __AFORM_HPP__

#include "Bureaucrat.hpp"
#include <string>
#include <exception>
#include <iostream>

class AForm 
{
    private:
        const std::string name;
        bool is_signed;
        const short grade_s;
        const short grade_e;
    
        
        public:
        AForm();
        AForm(const std::string &n, const short gs, const short ge);
        AForm(const AForm &o);
        AForm &operator=(const AForm &o);
        ~AForm(); // pure virtual
        
        const std::string &getName() const;
        bool getSigned() const;
        short getGradeToSign() const;
        short getGradeToExecute() const;
        
        void beSigned(Bureaucrat &o);
        virtual void execute(Bureaucrat const &executor) const = 0;
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
    };
    
std::ostream &operator<<(std::ostream &out, const AForm &f);
#endif