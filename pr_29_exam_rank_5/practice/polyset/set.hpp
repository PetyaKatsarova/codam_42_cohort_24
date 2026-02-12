#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set {
	searchable_bag *bag;

	public:
		set(searchable_bag &);
		set(const set &);
		set &operator=(const set &);
		~set();

		bool has(int) const;
		void insert(int);
		void insert(int *, int) ;
		void print() const;
		void clear();
		searchable_bag& get_bag() const;
};

#endif
