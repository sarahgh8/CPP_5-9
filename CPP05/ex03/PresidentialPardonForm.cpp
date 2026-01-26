#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string &t): AForm("PresidentialPardonForm", 25, 5), target(t)
{
    std::cout << "PresidentialPardonForm: Parameterized constructor\n";
}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &o): AForm(o), target(o.target)
{
    std::cout << "PresidentialPardonForm: Copy constructor\n";
}
PresidentialPardonForm::~PresidentialPardonForm()
{
    std::cout << "PresidentialPardonForm: desstructor\n";
}
PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm &o)
{
    if(target != o.target)
        target = o.target;
    return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const &exec) const
{
    if(!getSigned())
        throw std::runtime_error("Not signed\n");
    if(exec.getGrade() > getGradeToExecute())
        throw GradeTooLowException();
    std::cout << target << " has been pardoned by Zaphod Beeblebrox.\n";
}