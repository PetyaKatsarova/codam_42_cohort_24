

/**
 * Deque stands for Double-Ended Queue. It's a sequence container that allows you to add or remove elements efficiently from both the front and the back.
 * 
 * Deque can act as both stack and Queue.
It is useful in many problems where we need to have a subset of all operations also like insert/remove at front and insert/remove at the end.
 */

 #include <deque>
#include <iostream>
using namespace std;

//int main()
//{
//    deque<int> d1;

//    // Declare and initialize a deque with some values
//    deque<int> d2 = {10, 20, 30, 40};
//    for (int val : d2) {
//        cout << val << " ";
//    }
//    cout << endl;
//    return 0;
//}

//#include <iostream>
//#include <deque>
//using namespace std;

//int main() {
//    deque<int> d;
    
//    // Adding elements at the back
//    d.push_back(10);
//    d.push_back(20);
//    d.push_back(30);
    
//    // Displaying elements
//    cout << "Elements in deque (added using push_back): ";
//    for (int val : d) {
//        cout << val << " ";
//    }
//    cout << endl;

//    return 0;
//}

// rmv last el
#include <iostream>
#include <deque>
using namespace std;

int main() {
    deque<int> d = {10, 20, 30, 40};
    cout << "Original deque: ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;
    
    // Removing the last element
    d.pop_back();
    
    cout << "Deque after pop_back(): ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}