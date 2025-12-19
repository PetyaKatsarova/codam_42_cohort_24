#include "RPN.hpp"

RPN::RPN(const std::string& line) {
    // todo: populate stack
    int len = 0;
    while (line[len])
        len++;
    int i = 0;
    while (line[i]) {
        if (line[i] != ' ') {
            _nums.push(line[i]);
            i++;
        }
    }
}

RPN::RPN(const RPN& other) : _nums(other._nums) {}
RPN::~RPN() {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _nums = other._nums;
    }
    return *this;
}

bool RPN::validateInput(const std::string& argv) {
    if (argv.empty())
        return false;
    
    return true;
}