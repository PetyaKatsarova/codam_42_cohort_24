#include "Bureacrat.hpp"
#include "Form.hpp"
#include <string>
#include <iostream>
#include <exception>


//g++ -std=c++11 -Wall -Wextra main.cpp Bureacrat.cpp Form.cpp
int main()
{
    Form form("form1", 42, 22);
	Form f2(form);
	Bureacrat b("B1", 42); // valid

    std::cout << form << std::endl;

    std::cout << "-- deep cpy --" << std::endl;
    std::cout << "form._name addr: " << static_cast<const void*>(form.getName().data()) << std::endl;
    std::cout << "f2._name addrs:  " << static_cast<const void*>(f2.getName().data()) << std::endl;

    std::cout << "-- form signing funcs --\n";
    std::cout << b << std::endl;
    try{
		std::cout << "b.setgrade 151\n";
        b.setGrade(151);
    } catch (const std::exception &e) {
    	std::cout << e.what() << std::endl;
    }
	b.setGrade(42);
    b.signForm(f2); // valid
    printf("form req_sign: %d\n", f2.getReqSigninGrade());
    b.decrementGrade();
    printf("bureacrat decremented grade: %d\n", b.getGrade());
    b.signForm(f2);
    return 0;
}