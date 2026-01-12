#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat()
{
    std::cout << "Bureaucrat: Default Constructor\n";
}
Bureaucrat::Bureaucrat(const std::string &n, short g): name(n), grade(g)
{
    if(g < 1)
        throw Bureaucrat::GradeTooHighException();
    if(g > 150)
        throw Bureaucrat::GradeTooLowException();
    std::cout << "Bureaucrat: Parameterized Constructor\n";
}

Bureaucrat::Bureaucrat(const Bureaucrat &o)
{
    this->grade = o.grade;
    std::cout << "Bureaucrat: Copy Constructor\n";
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &o)
{
    if(this != &o)
        this->grade = o.grade;
    std::cout << "Bureaucrat: Copy Assignment Operator\n";
    return *this;
}

Bureaucrat::~Bureaucrat()
{
    std::cout << "Bureaucrat Destructor\n";
}

const std::string &Bureaucrat::getName() const
{
    return this->name;
}

short Bureaucrat::getGrade() const
{
    return this->grade;
}

void Bureaucrat::incrementGrade()
{
    if (this->grade <= 1)
        throw Bureaucrat::GradeTooHighException();
    this->grade--;
}

void Bureaucrat::decrementGrade()
{
    if (this->grade >= 150)
        throw Bureaucrat::GradeTooLowException();
    this->grade++;
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b)
{
    out << b.getName() << ", bureaucrat grade " << b.getGrade();
    return out;
}

void Bureaucrat::signForm(Form &form)
{
    try
    {
        form.beSigned(*this);
        std::cout << this->name << " signed " << form.getName() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << this->name << " couldn't sign " << form.getName()
                  << " because " << e.what();
    }
}