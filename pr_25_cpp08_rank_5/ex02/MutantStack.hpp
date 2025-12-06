#ifndef MUTANT_STACK_HPP
#define MUTANT_STACK_HPP

#include <stack>
#include <deque>

/**
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
class MutantStack : public std::stack<T, Container> {
	public:

		MutantStack() {}
		MutantStack(const MutantStack& other) : std::stack<T, Container>(other) {}
		~MutantStack() {}

		MutantStack& operator=(const MutantStack& other) {
			std::stack<T, Container>::operator=(other);
			return *this;
		}
		
		//(expose container's iterator types)
		typedef typename Container::iterator iterator;
		typedef typename Container::const_iterator const_iterator;
		typedef typename Container::reverse_iterator reverse_iterator;
		typedef typename Container::const_reverse_iterator const_reverse_iterator;

		iterator begin() { return this->c.begin(); }
		iterator end()   { return this->c.end(); }

		const_iterator begin() const { return this->c.begin(); }
		const_iterator end()   const { return this->c.end(); }

		reverse_iterator rbegin() { return this->c.rbegin(); }
		reverse_iterator rend()   { return this->c.rend(); }

		const_reverse_iterator rbegin() const { return this->c.rbegin(); }
		const_reverse_iterator rend()   const { return this->c.rend(); }
};

#endif