#include "set.hpp"

set::set(searchable_bag& sb) : sbag(sb) {}

set::set(const set& other) : sbag(other.sbag) {}

set& set::operator=(const set& other) {
	if (this != &other)
		sbag = other.sbag;
	return *this;
}

set::~set() {}

void set::insert(int num) {
	if (!sbag.has(num))
		sbag.insert(num);
}

void set::insert(int *arr, int size) {
	for (int i = 0; i < size; i++)
		sbag.insert(arr[i]);
}

void set::print() const {
	sbag.print();
}

void set::clear() {
	sbag.clear();
}

bool set::has(int num) const {
	return (sbag.has(num));
}

// !!remember: & return by ref: &is never null!! guaranteed
// *sbag: dereference the stored ptr
searchable_bag& set::get_bag() const {
	return sbag;
}