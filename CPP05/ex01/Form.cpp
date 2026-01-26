#include "Form.hpp"

Form::Form(): name("Default Form"), is_signed(false), grade_s(75), grade_e(50)
{
    std::cout << "Form: Default Constructor\n";
}

Form::Form(const std::string &n, const short gs, const short ge): name(n), is_signed(false), grade_s(gs), grade_e(ge)
{
    if (gs < 1 || ge < 1)
        throw Form::GradeTooHighException();
    if (gs > 150 || ge > 150)
        throw Form::GradeTooLowException();
    std::cout << "Form: Parameterized Constructor\n";
}

Form::Form(const Form &o): name(o.name), grade_s(o.grade_s), grade_e(o.grade_e)
{
    is_signed = o.is_signed;
    std::cout << "Form: Copy Constructor\n";
}

Form &Form::operator=(const Form &o)
{
    if(this != &o)
        is_signed = o.is_signed;
    return *this;
}

Form::~Form()
{
    std::cout << "Form: Destructor\n";
}

const std::string &Form::getName() const
{
    return this->name;
}

bool Form::getSigned() const
{
    return this->is_signed;
}

short Form::getGradeToSign() const
{
    return this->grade_s;
}

short Form::getGradeToExecute() const
{
    return this->grade_e;
}

void Form::beSigned(Bureaucrat &o)
{
    if (o.getGrade() > this->grade_s)
        throw Form::GradeTooLowException();
    this->is_signed = true;
}

std::ostream &operator<<(std::ostream &out, const Form &f)
{
    out << "Form " << f.getName()
        << ", signed: " << (f.getSigned() ? "yes" : "no")
        << ", grade to sign: " << f.getGradeToSign()
        << ", grade to execute: " << f.getGradeToExecute();
    return out;
}