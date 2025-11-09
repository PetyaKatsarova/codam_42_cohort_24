#include "Bureacrat.hpp"
#include "Form.hpp"
#include <string>
#include <iostream>
#include <exception>


//g++ -std=c++11 -Wall -Wextra main.cpp Bureacrat.cpp Form.cpp
int main()
{
    Form form("form1", 42, 22);
    std::cout << form << std::endl;

    // test deep copy form
    printf("-- deep cpy --\n");
    Form f2(form);
    std::cout << "form._name addr: " << static_cast<const void*>(form.getName().data()) << std::endl;
    printf("f2._name addrs:  %p\n", static_cast<const void*>(f2.getName().data()));
    printf("-- form signing funcs --\n");
    Bureacrat b("B1", 42); // valid
    std::cout << b << std::endl;
    try{
        b.setGrade(151);
    } catch (const std::exception &e) {
        printf("%s\n", e.what());
    }
    b.signForm(f2);
    printf("form req_sign: %d\n", f2.getReqSigninGrade());
    b.decrementGrade();
    printf("bureacrat decremented grade: %d\n", b.getGrade());
    b.signForm(f2);
    return 0;
}