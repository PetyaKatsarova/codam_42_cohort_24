#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set {
	public:
			set(searchable_bag &bag);
			set(const set &copy);
			set &operator=(const set &assign);
			~set();
			//method overloading - same name different param
			void insert(int value);
			void insert(int *value, int count);
			bool has(int value) const;
			void print() const;
			void clear();
			const searchable_bag &get_bag() const; //main needs

	private:
		searchable_bag& _bag; //composition - reference variable
};

#endif
