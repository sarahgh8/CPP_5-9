#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &t): AForm("ShrubberyCreationForm", 145, 137), target(t)
{
    std::cout << "ShrubberyCreationForm: Parameterized constructor\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &o): AForm(o), target(o.target)
{
    std::cout << "ShrubberyCreationForm: Copy constructor\n";
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
    std::cout << "ShrubberyCreationForm: Destructor\n";
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm &o)
{
    if(o.target != target)
        target = o.target;
    return *this;
}


void ShrubberyCreationForm::execute(Bureaucrat const &exec) const
{
    if(!getSigned())
        throw std::runtime_error("Not signed\n");
    if(exec.getGrade() > getGradeToExecute())
        throw AForm::GradeTooLowException();
    
    std::ofstream file;
    std::string filename = target + "_shrubbery";
    file.open(filename.c_str());
    
    if(!file.is_open())
        throw std::runtime_error("Could not create file");
    
    file << "                                                         .\n";
    file << "                                              .         ;  \n";
    file << "                 .              .              ;%     ;;   \n";
    file << "                   ,           ,                :;%  %;   \n";
    file << "                    :         ;                   :;%;'     .,   \n";
    file << "           ,.        %;     %;            ;        %;'    ,;\n";
    file << "             ;       ;%;  %%;        ,     %;    ;%;    ,%'\n";
    file << "              %;       %;%;      ,  ;       %;  ;%;   ,%;' \n";
    file << "               ;%;      %;        ;%;        % ;%;  ,%;'\n";
    file << "                `%;.     ;%;     %;'         `;%%;.%;'\n";
    file << "                 `:;%.    ;%%. %@;        %; ;@%;%'\n";
    file << "                    `:%;.  :;bd%;          %;@%;'\n";
    file << "                      `@%:.  :;%.         ;@@%;'   \n";
    file << "                        `@%.  `;@%.      ;@@%;         \n";
    file << "                          `@%%. `@%%    ;@@%;        \n";
    file << "                            ;@%. :@%%  %@@%;       \n";
    file << "                              %@bd%%%bd%%:;     \n";
    file << "                                #@%%%%%:;;\n";
    file << "                                %@@%%%::;\n";
    file << "                                %@@@%(o);  . '         \n";
    file << "                                %@@@o%;:(.,'         \n";
    file << "                            `.. %@@@o%::;         \n";
    file << "                               `)@@@o%::;         \n";
    file << "                                %@@(o)::;        \n";
    file << "                               .%@@@@%::;         \n";
    file << "                               ;%@@@@%::;.          \n";
    file << "                              ;%@@@@%%:;;;. \n";
    file << "                          ...;%@@@@@%%:;;;;,..    Gilo97\n";
    
    file.close();
}