#include "RPN.hpp"
#include <cctype> // std::isdigit()
#include <stdexcept> // std::runtime_error()

RPN::RPN() : _nums() {}

RPN::RPN(const RPN& other) : _nums(other._nums) {}
RPN::~RPN() {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _nums = other._nums;
    }
    return *this;
}

bool RPN::validateInput(const std::string& argv) const {
    if (argv.empty()) { return false; }

	int numCount = 0;
	int opCount  = 0;

    for (size_t i = 0; i < argv.size(); ++i) {
		char c = argv[i];
		
		if (c == ' ') { continue; }
		if (isdigit(c))
			numCount++;
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			opCount++;
			if (numCount < opCount + 1)
				return false;
		} else {
			return false;
		}
	}
	return (opCount == numCount - 1);
}

int RPN::calc(int num1, int num2, char sign) const {
	switch (sign) {
		case '+': return num1 + num2;
		case '-': return num1 - num2;
		case '*': return num1 * num2;
		case '/':
			if (num2 == 0)
				throw std::runtime_error("Error: better not devide by 0\n");
			return num1 / num2;
		default:
			throw std::runtime_error("Error: invalid operator");
	}
}

// c style: faster, num is always < 10
/**
	pop() removes but returns void (no value)
 */
int RPN::calculate(const std::string& input) {
	//clear stack from prev calculations:
	while (!_nums.empty())
		_nums.pop();
		
	for (size_t i = 0; input[i]; ++i) {
		char c = input[i];
		if (c == ' ') { continue; }

		if (std::isdigit(c)) {
			_nums.push(c - '0');
		} else {
			//std::cout << "sign\n";
			if (_nums.size() < 2) {
				throw std::runtime_error("Error: insufficient operands\n");
			}
			int		num2 = _nums.top();
			_nums.pop(); // rmv lst(top) el
			int		num1 = _nums.top();
			_nums.pop();
			_nums.push(calc(num1, num2, c));
		}
	}
	
	if (_nums.size() != 1) {
		 throw std::runtime_error("Error: invalid expression");
	}
	return _nums.top();
}
