#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(): name("default"), is_signed(false), grade_s(150), grade_e(150)
{
    std::cout << "AForm: Default constructor\n";
}

AForm::AForm(const std::string &n, const short gs, const short ge): name(n), is_signed(false), grade_s(gs), grade_e(ge)
{
    if (gs < 1 || ge < 1)
        throw GradeTooHighException();
    if (gs > 150 || ge > 150)
        throw GradeTooLowException();
    std::cout << "AForm: Parameterized constructor\n";
}

AForm::AForm(const AForm &o): name(o.name), is_signed(o.is_signed), grade_s(o.grade_s), grade_e(o.grade_e)
{
    std::cout << "AForm: Copy constructor\n";
}

AForm &AForm::operator=(const AForm &o)
{
    if (this != &o)
        is_signed = o.is_signed;
    std::cout << "AForm: Assignment operator\n";
    return *this;
}

AForm::~AForm()
{
    std::cout << "AForm: Destructor\n";
}

const std::string &AForm::getName() const
{
    return name;
}

bool AForm::getSigned() const
{
    return is_signed;
}

short AForm::getGradeToSign() const
{
    return grade_s;
}

short AForm::getGradeToExecute() const
{
    return grade_e;
}

void AForm::beSigned(Bureaucrat &o)
{
    if (o.getGrade() > grade_s)
        throw GradeTooLowException();
    is_signed = true;
}

std::ostream &operator<<(std::ostream &out, const AForm &f)
{
    out << "Form: " << f.getName() 
        << ", Signed: " << (f.getSigned() ? "Yes" : "No")
        << ", Grade to sign: " << f.getGradeToSign()
        << ", Grade to execute: " << f.getGradeToExecute();
    return out;
}
