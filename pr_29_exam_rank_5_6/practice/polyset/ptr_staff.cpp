#include <iostream>

/**
 * Stack Memory:
┌─────────────────────────────────┐
│ Address: 0x7ffc5b701ad8         │
│ Variable: num                   │
│ Value: 5 → 10                   │  ← The actual integer
└─────────────────────────────────┘
         ↑
         │ points to
         │
┌─────────────────────────────────┐
│ Address: 0x7ffc5b701ad0         │  ← ptrnum itself lives here
│ Variable: ptrnum                │
│ Value: 0x7ffc5b701ad8           │  ← Stores num's address
└─────────────────────────────────┘
 */
int main() {
	int num = 5;
	int *ptrnum = &num;

	std::cout << "*ptrnum = " << *ptrnum << std::endl;
	std::cout << " ptrnum = " << ptrnum << std::endl;
	std::cout << "&ptrnum = " << &ptrnum << std::endl;
	*ptrnum = 10;
	std::cout << "*ptrnum = " << *ptrnum << std::endl;
	std::cout << " ptrnum = " << ptrnum << std::endl;
	std::cout << "   &num = " << &num << std::endl;
	std::cout << "    num = " << num << std::endl;
	return 0;
}