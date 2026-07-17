#ifndef SET_BAG_HPP
#define SET_BAG_HPP

#include "searchable_bag.hpp"

class set {
	private:
		searchable_bag* sbag;

	public:
		set(searchable_bag& sb);
		set(const set& other);
		set& operator=(const set& other);
		~set();

		bool has(int) const;
		void insert(int);
		void insert(int *, int);
		void print() const;
		void clear();
		searchable_bag& get_bag() const;
};

#endif




















//class set {
//	searchable_bag* bag;

//	public:
//		set(searchable_bag&);
//		set(const set &);
//		set& operator=(const set&);
//		~set();

//		bool has(int) const;
//		void insert(int);
//		void insert(int *array, int size);
//		void print() const;
//		void clear();
//		searchable_bag& get_bag() const;
//};

//#endif