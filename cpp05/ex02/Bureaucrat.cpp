/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-jira <mel-jira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:19:39 by mel-jira          #+#    #+#             */
/*   Updated: 2024/06/28 09:37:17 by mel-jira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name("default_name"), grade(150){
    std::cout << "Bureaucrat default constructor was called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string const _name, int _grade): name(_name){
    std::cout << "Bureaucrat paramater constructor was called" << std::endl;
    if (_grade < 1){
        throw GradeTooHighException();
    }
    else if (_grade > 150){
        throw GradeTooLowException();
    }
    else
        this->grade = _grade;
}

Bureaucrat::~Bureaucrat(){
    std::cout << "Bureaucrat destructor was called" << std::endl;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &cpy_asy){
    std::cout << "Bureaucrat calling copy assignment" << std::endl;
    (void)cpy_asy;
    return (*this);
}

Bureaucrat::Bureaucrat(Bureaucrat const  &cpy_cons){
    std::cout << "Bureaucrat calling copy constructor" << std::endl;
    *this = cpy_cons;
}

std::ostream& operator<<(std::ostream &out, Bureaucrat& obj)
{
    out << obj.getName() << ", bureaucrat grade " <<  obj.getGrade() << std::endl;
    return (out);
}

const char* Bureaucrat::GradeTooHighException::what(void) const throw()
{
    return "Grade too High";
}

const char* Bureaucrat::GradeTooLowException::what(void) const throw()
{
    return "Grade too Low";
}

std::string Bureaucrat::getName() const{
    return (this->name);
}

int Bureaucrat::getGrade() const{
    return (this->grade);
}

void Bureaucrat::increaseGrade(){
    if (grade <= 1)
        throw GradeTooHighException();
    else
        this->grade--;
}

void Bureaucrat::decreaseGrade(){
    if (grade >= 150)
        throw GradeTooLowException();
    else
        this->grade++;
}

void Bureaucrat::signForm(AForm &form){
    try {
        form.beSigned(*this);
        std::cout << this->name << " signed " << form.getName() << std::endl;
    }
    catch (AForm::GradeTooLowException &e) {
        std::cout << name << " couldn’t sign " << form.getName() << " because " << e.what() << std::endl;
    }
}

void    Bureaucrat::executeForm(AForm const & form){
    try {
        if (form.getSign())
            form.execute(*this);
        else
            throw AForm::FormNotSignedException();
    } catch (std::exception& e) {
        std::cout << name << " couldn't execute " << form.getName() << " because " << e.what() << std::endl;
    }
}
