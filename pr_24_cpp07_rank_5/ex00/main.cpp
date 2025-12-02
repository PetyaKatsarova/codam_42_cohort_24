#include <iostream>
#include <string>
// #include <Array.hpp>
#include "whatever.hpp"

int main( void ) {
int a = 2;
int b = 3;
::swap( a, b );
std::cout << "a = " << a << ", b = " << b << std::endl;
std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
std::string c = "chaine1";
std::string d = "chaine2";
::swap(c, d);
std::cout << "c = " << c << ", d = " << d << std::endl;
std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
return 0;
}


// int main() {
//     std::cout << "=== Test 1: Swap Integers ===" << std::endl;
//     int a = 2;
//     int b = 3;
    
//     std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
//     ::swap(a, b);  // :: means use our swap, not std::swap
//     std::cout << "After swap:  a = " << a << ", b = " << b << std::endl;
    
    
//     std::cout << "\n=== Test 2: Min/Max Integers ===" << std::endl;
//     std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
//     std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
    
    
//     std::cout << "\n=== Test 3: Strings ===" << std::endl;
//     std::string c = "chaine1";
//     std::string d = "chaine2";
    
//     std::cout << "Before swap: c = " << c << ", d = " << d << std::endl;
//     ::swap(c, d);
//     std::cout << "After swap:  c = " << c << ", d = " << d << std::endl;
//     std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
//     std::cout << "max(c, d) = " << ::max(c, d) << std::endl;
    
    
//     std::cout << "\n=== Test 4: Floats ===" << std::endl;
//     float x = 3.14f;
//     float y = 2.71f;
    
//     std::cout << "x = " << x << ", y = " << y << std::endl;
//     std::cout << "min(x, y) = " << ::min(x, y) << std::endl;
//     std::cout << "max(x, y) = " << ::max(x, y) << std::endl;
//     ::swap(x, y);
//     std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    
    
//     std::cout << "\n=== Test 5: Equal Values ===" << std::endl;
//     int equal1 = 42;
//     int equal2 = 42;
    
//     std::cout << "equal1 = " << equal1 << ", equal2 = " << equal2 << std::endl;
//     std::cout << "min(equal1, equal2) returns second = " << ::min(equal1, equal2) << std::endl;
//     std::cout << "max(equal1, equal2) returns second = " << ::max(equal1, equal2) << std::endl;
    
//     // Verify it returns second by address
//     std::cout << "\nAddress verification:" << std::endl;
//     std::cout << "&equal1 = " << &equal1 << std::endl;
//     std::cout << "&equal2 = " << &equal2 << std::endl;
//     std::cout << "&min(equal1, equal2) = " << &::min(equal1, equal2) << std::endl;
//     std::cout << "&max(equal1, equal2) = " << &::max(equal1, equal2) << std::endl;
    
    
//     std::cout << "\n=== Test 6: Doubles ===" << std::endl;
//     double d1 = 1.5;
//     double d2 = 2.5;
    
//     std::cout << "d1 = " << d1 << ", d2 = " << d2 << std::endl;
//     std::cout << "min = " << ::min(d1, d2) << std::endl;
//     std::cout << "max = " << ::max(d1, d2) << std::endl;
    
    
//     std::cout << "\n=== Test 7: Characters ===" << std::endl;
//     char ch1 = 'a';
//     char ch2 = 'z';
    
//     std::cout << "ch1 = " << ch1 << ", ch2 = " << ch2 << std::endl;
//     std::cout << "min = " << ::min(ch1, ch2) << std::endl;
//     std::cout << "max = " << ::max(ch1, ch2) << std::endl;
//     ::swap(ch1, ch2);
//     std::cout << "After swap: ch1 = " << ch1 << ", ch2 = " << ch2 << std::endl;
    
    
//     std::cout << "\n=== Test 8: Negative Numbers ===" << std::endl;
//     int neg1 = -10;
//     int neg2 = -5;
    
//     std::cout << "neg1 = " << neg1 << ", neg2 = " << neg2 << std::endl;
//     std::cout << "min = " << ::min(neg1, neg2) << std::endl;
//     std::cout << "max = " << ::max(neg1, neg2) << std::endl;
    
    
//     std::cout << "\n=== Test 9: Mixed Signs ===" << std::endl;
//     int pos = 10;
//     int neg = -10;
    
//     std::cout << "pos = " << pos << ", neg = " << neg << std::endl;
//     std::cout << "min = " << ::min(pos, neg) << std::endl;
//     std::cout << "max = " << ::max(pos, neg) << std::endl;
    
    
//     std::cout << "\n=== Test 10: Subject Test ===" << std::endl;
//     int sa = 2;
//     int sb = 3;
    
//     ::swap(sa, sb);
//     std::cout << "a = " << sa << ", b = " << sb << std::endl;
//     std::cout << "min(a, b) = " << ::min(sa, sb) << std::endl;
//     std::cout << "max(a, b) = " << ::max(sa, sb) << std::endl;
    
//     std::string sc = "chaine1";
//     std::string sd = "chaine2";
    
//     ::swap(sc, sd);
//     std::cout << "c = " << sc << ", d = " << sd << std::endl;
//     std::cout << "min(c, d) = " << ::min(sc, sd) << std::endl;
//     std::cout << "max(c, d) = " << ::max(sc, sd) << std::endl;
    
//     return 0;
// }

// #define MAX_VAL 750
// int main(int, char**)
// {
//     Array<int> numbers(MAX_VAL);
//     int* mirror = new int[MAX_VAL];
//     srand(time(NULL));
//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         const int value = rand();
//         numbers[i] = value;
//         mirror[i] = value;
//     }
//     //SCOPE
//     {
//         Array<int> tmp = numbers;
//         Array<int> test(tmp);
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         if (mirror[i] != numbers[i])
//         {
//             std::cerr << "didn't save the same value!!" << std::endl;
//             return 1;
//         }
//     }
//     try
//     {
//         numbers[-2] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
//     try
//     {
//         numbers[MAX_VAL] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         numbers[i] = rand();
//     }
//     delete [] mirror;//
//     return 0;
// }