#include <iostream>
#include <string>

class Student {
	private:
		std::string _login;

	public:
		Student() : _login("stDefault") {
			std::cout << "Student " << this->_login << " is born" << std::endl;
		}

		~Student() {
			std::cout << "Student " << this->_login << " died" << std::endl;
		}
};

// c++ main.cpp && ./a.out
int main() {

	Student* students = new Student[42];
	delete[] students;

	return (0);
}