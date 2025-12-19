#ifndef RPN_HEADER
#define RPN_HEADER

#include <stack>
#include <string>

class RPN {
    public: // for testing only rmv 
    std::stack<char> _nums;

    public:
        RPN(const std::string& line);
        RPN(const RPN& other);
        ~RPN();

        RPN& operator=(const RPN& other);

        bool validateInput(const std::string& argv);// check if int, int < 10, or "+ - / *"
        int calculate();
};

#endif