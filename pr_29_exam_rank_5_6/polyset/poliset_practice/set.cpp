#include "set.hpp"

set::set(searchable_bag& sb) : sbag(sb) {}

set::set(const set &other) : sbag(other.sbag) {}

set& set::operator=(const set &other) {
	(void) other;
	return *this;
}

set::~set() {}

bool set::has(int v) const {
	if (sbag.has(v))
		return true;
	return false;
}

void set::insert(int num) {
	if (!this->has(num))
		sbag.insert(num);
}

void set::insert(int *arr, int size)  {
	for (int i = 0; i < size; i++)
		this->insert(arr[i]);
}

void set::print() const {
	sbag.print();
}

void set::clear() {
	sbag.clear();
}
