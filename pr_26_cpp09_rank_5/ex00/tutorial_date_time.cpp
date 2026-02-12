#include <ctime>
#include <iostream>

int main() {
	time_t timestamp;
	//time(&timestamp); //cur date in secs from 1970

	std::cout << timestamp << '\n';
	std::cout << ctime(&timestamp); // formatted date even with \n
	return 0;
}