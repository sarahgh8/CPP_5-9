#ifndef __BUREAUCRAT_HPP__
#define __BUREAUCRAT_HPP__

#include <string>
#include <exception>
#include <iostream>

class Bureaucrat
{
    private:
        const std::string name;
        short grade;
    public:
        Bureaucrat();
        Bureaucrat(const std::string &n, short g);
        Bureaucrat(const Bureaucrat &o);
        Bureaucrat &operator=(const Bureaucrat &o);
        ~Bureaucrat();

        const std::string &getName() const;
        short getGrade() const;
        void incrementGrade();
        void decrementGrade();
        void signForm(Form &form);
    
    class GradeTooHighException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return "Grade is too High!";
            }
    };

    class GradeTooLowException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return "Grade is too Low!";
            }
    };
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b);


#endif