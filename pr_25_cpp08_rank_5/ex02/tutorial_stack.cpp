#include <stack>
#include <vector>
#include <deque>
#include <iostream>

/**
 * Stack container follows LIFO (Last In First Out) order of insertion and deletion. It means that most recently inserted element is removed first and the first inserted element will be removed last. This is done by inserting and deleting elements at only one end of the stack which is generally called the top of the stack.
 * 
 * time complexity:
    Insert an element (push)	O(1)
	Delete an element (pop)		O(1)
	Access top element (peek)	O(1)
	Traverse the stack			O(n)
 */

 /**
  * NB!!
  * std::stack is a container adaptor, which means it uses another container internally. By default, it uses std::deque.
  * 
  * int main() {
  std::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);

  const std::deque<int>& d = s._Get_container();
  for (int i : d) {
    std::cout << i << ' ';
  }
}
  */

// iter option 1: copy to another container
int main() {
    std::stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    
    // Copy to vector by popping (preserves order)
    std::stack<int> temp = s;  // Make a copy
    std::vector<int> vec;
    
    while (!temp.empty()) {
        vec.push_back(temp.top());
        temp.pop();
    }
    
    // Now iterate vector
    std::cout << "Elements (top to bottom): ";
    for (int x : vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    // Output: 40 30 20 10
    
    // Original stack still intact
    std::cout << "Original stack top: " << s.top() << std::endl;  // 40
    std::cout << "Original stack size: " << s.size() << std::endl;  // 4
    
    return 0;
}



// valgrind c++ stack_tutorial.cpp && ./a.out
//using namespace std;
//int main() {
//	stack<int> st;
//	if (st.empty())
//		cout << "Stack is empty " << endl;
//	st.push(10);
//	st.push(5);

//	cout << "Top(last) el: " << st.top() << endl;
//	st.pop();
//	cout << "Top(last) el after pop: " << st.top() << endl;
//	cout << "stack.size() = " << st.size() << endl;
//	return 0;
//}