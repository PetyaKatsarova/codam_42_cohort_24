/*reinterpret_cast is 
used to convert a pointer of some data type into a pointer of another data type, even if the data types before and after conversion are different.
It does not check if the pointer type and data pointed by the pointer is same or not.

data_type *var_name = 
       reinterpret_cast <data_type *>(pointer_variable);

It doesn't have any return type. It simply converts the pointer type.



reinterpret_cast is a very special and dangerous type of casting operator. And is suggested to use it using proper data type i.e., (pointer data type should be same as original data type).
It can typecast any pointer to any other data type.
It is used when we want to work with bits.
If we use this type of cast then it becomes a non-portable product. So, it is suggested not to use this concept unless required.
It is only used to typecast any pointer to its original type.
Boolean value will be converted into integer value i.e., 0 for false and 1 for true.
*/

#include <iostream>
using namespace  std;

// c++ reinterpret_cast.cpp && ./a.out
int main() {
	int* ptr = new int(65);
	char *ch = reinterpret_cast<char*>(ptr);
	cout << *ptr << endl; // val as int:oiriginal
	cout << *ch << endl; // val as char: changed
	cout << ptr << endl; // address of the ptr
	cout << ch << endl; // val after cast: same as *ch
	return 0;
}