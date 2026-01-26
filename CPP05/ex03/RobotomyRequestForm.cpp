#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string &t): AForm("RobotomyRequestForm", 72, 45), target(t)
{
    std::cout << "RobotomyRequestForm: Parameterized constructor\n";
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &o): AForm(o), target(o.target)
{
    std::cout << "RobotomyRequestForm: Copy constructor\n";
}

RobotomyRequestForm::~RobotomyRequestForm()
{
    std::cout << "RobotomyRequestForm: Destructor\n";
}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm &o)
{
    if(target != o.target)
        target = o.target;
    std::cout << "RobotomyRequestForm: Assignment operator\n";
    return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const &exec) const
{
    if(!getSigned())
        throw std::runtime_error("Not signed\n");
    if(exec.getGrade() > getGradeToExecute())
        throw GradeTooLowException();
    std::cout << "Buzzzzzz ... zzzzzzzzz ... Zzzzzzzzzzz\n";
    srand(time(0));
    int rand_num = rand();
    if(rand_num % 2)
        std::cout << "Robotomy Failed\n";
    else
        std::cout << target << " has been robotomized successfully\n";
}
