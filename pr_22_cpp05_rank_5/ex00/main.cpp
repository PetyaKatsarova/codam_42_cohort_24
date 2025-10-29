#include "Bureacrat.hpp"
#include <iostream>
#include <cassert>

/**
!!NB: static_cast<const void*>(b.getName).c_str
you must call getName() and then c_str() to get the char buffer pointer. If you omit c_str() you either get a compile error (wrong syntax) or you get the address of the std::string object (not its internal buffer).
object address vs buffer address are different things. Use object addr to inspect where the std::string object lives; use c_str() pointer to inspect the character buffer (useful to detect if copy used a different buffer).
addr = static_cast<const void*>(&b.getName())
Address of the std::string object (the string object’s memory, inside the Bureacrat instance).
buf_addr = static_cast<const void*>(b.getName().c_str())
Pointer to the first character of the string’s internal buffer (the char data).

Use assert for developer checks/invariants only. Do not use for user input validation or error handling in production — use exceptions or explicit checks.
For compile-time checks use static_assert.
*/
static void ft_print(const char *tag, const Bureacrat &b)
{
    std::cout << tag
            << " name='" << b.getName() << "',"
            << " grade=" << b.getGrade() << ","
            << " addr=" << static_cast<const void*>(&b.getName())  << ", " // get addrs of string obj
            << " buf_addr=" << static_cast<const void*>(b.getName().c_str()) // get addr of first char of string's internal buffer
            << "\n";
}   


//g++ -std=c++11 -Wall -Wextra main.cpp Bureacrat.cpp -o main
int main()
{
    Bureacrat b("Beky", 149);
    Bureacrat e("Echo", 2);
    std::cout << b << std::endl;
    // ft_print("bla", b);
    std::cout << "--- CPY CONSTR ---\n";
    Bureacrat c(b);
    ft_print("b", b);
    ft_print("c", c);
    std::cout << "--- CPY ASSINGMENT ---\n";
    b = e; // calls cpy constr
    ft_print("b", b);
    ft_print("e", e);
    std::cout << "--- PLAY WITH GRADES ---\n";
    try {
        Bureacrat stupid("Stpd", 149);
        e.incrementGrade();
        std::cout << e << std::endl;
        stupid.decrementGrade();
        std::cout << stupid << std::endl;
        e.incrementGrade();
        std::cout << e << std::endl;
        stupid.decrementGrade();
        std::cout << stupid << std::endl;
    } 
    catch (const std::exception &e) {
        std::cerr << "Error adjusting grades: " << e.what() << '\n';
    }
  
    int x = 5;
    assert(x > 0); // OK in debug
    return 0;
}