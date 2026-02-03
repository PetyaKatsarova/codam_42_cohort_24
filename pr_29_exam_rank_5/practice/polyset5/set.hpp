#ifndef SET_HPP
#define SET_HPP
#include "searchable_bag.hpp"

class set {
	searchable_bag* bag;

	public:
		set(searchable_bag&);
		set(const set&);
		~set();
		set& operator=(const set &other);


		bool has(int val) const;
		void insert(int val);
		void insert(int *, int);
		void print() const;
		void clear();
		searchable_bag& get_bag() const;
};

#endif