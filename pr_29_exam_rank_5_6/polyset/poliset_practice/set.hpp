
#ifndef SET_HPP
#define SET_HPP
#include "searchable_bag.hpp"

class set {
private:
	searchable_bag& sbag;

public:
	set(searchable_bag&);
	set(const set &);
	set &operator=(const set &other);
	~set();

	bool has(int) const;
	void insert(int);
	void insert(int *, int) ;
	void print() const;
	void clear();
};


#endif