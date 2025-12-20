#ifndef RPN_HEADER
#define RPN_HEADER

#include <stack>
#include <string>

// todo: make it static: will not use objects, i think
class RPN {
    public: // for testing only rmv 
    std::stack<int> _nums; // default constr: create empty stack
	int calc(int num1, int num2, char sign) const;

    public:
        RPN();
        RPN(const RPN& other);
        ~RPN();

        RPN& operator=(const RPN& other);

        bool validateInput(const std::string& argv) const;
        int calculate(const std::string& input);
};

#endif