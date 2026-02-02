#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set {
	searchable_bag* bag;

	public:
		set(searchable_bag&);
		set(const set&);
		set& operator=(const set& other);
		~set();

	void insert(int);
	void insert(int *, int) ;
	void print() const;
	void clear();
	bool has(const int);
	searchable_bag&	get_bag() const;
};

#endif