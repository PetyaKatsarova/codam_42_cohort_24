#include "set.hpp"

set::set(searchable_bag& sb) : sbag(&sb) {}

set::set(const set& other) : sbag(other.sbag) {}

set& set::operator=(const set& other) {
	if (this != &other)
		sbag = other.sbag;
	return *this;
}

set::~set() {}

bool set::has(int n) const {
	if (sbag->has(n))
		return true;
	return false;
}

searchable_bag& set::get_bag() const {
	return *this->sbag;
}

void set::insert(int n) {
	if (!sbag->has(n))
		sbag->insert(n);
}

// insert in arraybag range of int: with size
void set::insert(int *arr, int size) {
	for (int i = 0; i < size; i++)
		this->insert(arr[i]);
}

void set::print() const {
	sbag->print();
}

void set::clear() {
	sbag->clear();
}
