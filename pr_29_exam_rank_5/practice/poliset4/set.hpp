
#ifndef SET_HPP
#define SET_HPP
#include "searchable_bag.hpp"
#include "array_bag.hpp"
#include "tree_bag.hpp"

class set {
private:
	searchable_bag& sbag;

public:

	set(searchable_bag& sb);
	set(const set& other);
	set& operator=(const set& other);
	~set();

	void insert(int);
	void insert(int *, int) ;
	void print() const;
	void clear();
	bool has(int) const;
	searchable_bag& get_bag() const;
};


#endif
