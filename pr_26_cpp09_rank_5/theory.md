Reverse Polish Notation (RPN), also called postfix notation, is a mathematical notation where operators follow their operands, eliminating the need for parentheses.

Standard (Infix)	RPN (Postfix)
3 + 4	              3 4 +
5 * 6	              5 6 *
(3 + 4) * 5	          3 4 + 5 *

std::stack<int> s;
s.push(9);
s.push(3);
s.push(7);
s.push(1);

// Stack state: [9, 3, 7, 1] (1 is on top)

s.top();  // Returns 1
s.pop();  // Removes 1
s.top();  // Returns 7
s.pop();  // Removes 7
s.top();  // Returns 3

std::map<int, int> m;
m[9] = 1;
m[3] = 2;
m[7] = 3;
m[1] = 4;

// Map automatically stores as: {1: 4, 3: 2, 7: 3, 9: 1}

for (auto& pair : m) {
    std::cout << pair.first << " ";
}
// Output: 1 3 7 9  (SORTED!)