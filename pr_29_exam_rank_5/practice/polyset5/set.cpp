#include "set.hpp"

set::set(searchable_bag& sbag) : bag(&sbag) {}

set::set(const set& other) : bag(other.bag) {}

set::~set() {}

set& set::operator=(const set &other) {
	if (this != &other) {
		bag = other.bag;
	}
	return *this;
}

bool set::has(int val) const {
	return (bag->has(val));
}

void set::insert(int val){
	if (!bag->has(val)) {
		bag->insert(val);
	}
}

void set::insert(int *ptr, int size) {
	for (int i = 0; i < size; i++) {
		this->insert(ptr[i]);
	}
}

void set::print() const{
	this->bag->print();
}

void set::clear(){
	this->bag->clear();
}

searchable_bag& set::get_bag() const{
	return *this->bag;
}