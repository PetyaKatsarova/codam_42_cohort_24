#include "set.hpp"

set::set(searchable_bag& sbag) : bag(&sbag) {}

set::set(const set& other) : bag(other.bag) {}

set& set::operator=(const set &other) {
	if (this != &other) {
		this->bag = other.bag;
	}
	return *this;
}

set::~set() {}

void set::insert(int val) {
	if (!this->bag->has(val))
		this->bag->insert(val);
}

void set::insert(int* arr, int range) {
	for (int i = 0; i < range; i++) {
		this->insert(arr[i]);
	}
}

void set::print() const {
	this->bag->print();
}

void set::clear() {
	this->bag->clear();
}

bool set::has(const int val) {
	return (this->bag->has(val));
}

searchable_bag& set::get_bag() const{
	return (*this->bag);
}