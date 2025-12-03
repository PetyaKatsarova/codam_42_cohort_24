#include <stack>
#include <queue>
#include <iostream>

/*Stack (LIFO)
stk.top() gives the last element that was pushed (the top of the stack).
stk.pop() removes that same top element.
*/
void stackDemo() {
    std::stack<int> stk;
    
    // Push
    stk.push(10);
    stk.push(20);
    stk.push(30);
    
     std::cout << "*** STACK ***\n";
    std::cout << "Top: " << stk.top() << std::endl;  // 30
    stk.pop();
    std::cout << "Top after pop: " << stk.top() << std::endl;  // 20
    std::cout << "Size: " << stk.size() << std::endl;

    while (!stk.empty()) {
        std::cout << stk.top() << " ";
        stk.pop();
    }
    std::cout << std::endl;
}

// FIFO
void queueDemo() {
    std::queue<int> q;
 
    q.push(10);
    q.push(20);
    q.push(30);
    
    std::cout << "\n*** QUEUE ***\n";
    std::cout << "Front: " << q.front() << std::endl;  // 10
    std::cout << "Back: " << q.back() << std::endl;    // 30
    
    // Pop (removes front)
    q.pop();
    std::cout << "Front after pop: " << q.front() << std::endl;  // 20
    
    // Process all
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

int main() {
    stackDemo();
    queueDemo();
    return 0;
}