#ifndef RPN_HEADER
#define RPN_HEADER

#include <stack>
#include <string>

class RPN {
    std::stack<std::string> _nums;

    public:
        RPN(std::string& line);
        RPN(const RPN& other);
        ~RPN();

        RPN& operator=(const RPN& other);

        bool validateInput(std::string& argv);// check if int, int < 10, or "+ - / *"
};

#endif