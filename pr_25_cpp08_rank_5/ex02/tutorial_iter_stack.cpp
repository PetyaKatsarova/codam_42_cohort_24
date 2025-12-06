#include <stack>
#include <deque>
#include <iostream>

/**
 * /**
 * in standard lib, stack is defined:
 * template<typename T, typename Container = std::deque<T>>
class stack {
	protected:
		Container c;
		
	public:
		void push(const T& val) { c.push_back(val); }
		void pop() { c.pop_back(); }
		T& top() { return c.back(); }
		size_t size() const { return c.size(); }
		etc
};
 */

template<typename T, typename Container = std::deque<T>>
class IterableStack : public std::stack<T, Container> {
	public:

		// get iterators from underlying container
		typedef typename Container::iterator it;
		typedef typename Container::const_iterator const_it;

		it begin() { return this->c.begin(); }
		it end()   { return this->c.end(); }

		const_it begin() const { return this->c.begin(); }
		const_it end()   const { return this->c.end(); }
};

int main() {
	IterableStack<int> it_st;

	it_st.push(10);
	it_st.push(20);
	it_st.push(30);
	it_st.push(40);
	
	std::cout << "Elements bottom to top: ";
	for (int s : it_st) {
		std::cout << s << " ";
	}

	std::cout << "\nTop: " << it_st.top() << std::endl;  // 40
    it_st.pop();
    std::cout << "After pop: " << it_st.top() << std::endl;  // 30
	return 0;
}