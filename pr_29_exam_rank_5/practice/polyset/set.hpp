#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set {
private:
	searchable_bag *_bag;
public:
	set(searchable_bag &);
	set(const set &);
	set &operator=(const set &);
	~set();
	void insert(int);
	void insert(int *, int);
	void print() const;
	void clear();
	bool has(int) const;
	searchable_bag &get_bag() const;
};

#endif
