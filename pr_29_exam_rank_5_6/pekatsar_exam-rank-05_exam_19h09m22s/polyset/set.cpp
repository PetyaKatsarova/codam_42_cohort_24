#include "set.hpp"

set::set(searchable_bag& sb) : sbag(sb) {}

set::set(const set &other) : sbag(other.sbag) {}

set& set::operator=(const set &other) {
	if (this != &other) {
		sbag = other.sbag;
	}
	return *this;
}

set::~set() {}

bool set::has(int num) const {
	return sbag.has(num);
}

void set::insert(int val) {
	if (!sbag.has(val))
		sbag.insert(val);
}

void set::insert(int *arr, int size)  {
	for (int i = 0; i < size; i++) {
		// if (!has(arr[i]))
			insert(arr[i]);
	}
}

void set::print() const {
	sbag.print();
}

void set::clear() {
	sbag.clear();
}

const searchable_bag& set::get_bag() const {
	return sbag;
}

	
