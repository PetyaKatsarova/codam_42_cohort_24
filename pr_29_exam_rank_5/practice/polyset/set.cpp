#include "set.hpp"

set::set(searchable_bag &bag) : bag(&bag) {}

set::set(const set & other) : bag(other.bag) {}

set &set::operator=(const set & other) {
	if (this != &other) {
		this->bag = other.bag;
	}
	return *this;
}

set::~set(){}

bool set::has(int num) const {
	return (bag->has(num));
}

void set::insert(int num) {
	if (!bag->has(num))
		bag->insert(num);
}

// append range of int with size into bag
void set::insert(int *ptr, int size)  {
	for (int i = 0; i < size; i++) {
		this->insert(ptr[i]);
	}
	//this->bag->insert(ptr, size); would bypass duplicate code
}

void set::print() const {
	this->bag->print();
}

void set::clear() {
	this->bag->clear();
}

searchable_bag& set::get_bag() const {
	return *this->bag;
}




































//set::set(searchable_bag &bag) : _bag(&bag) {}

//set::set(const set &other) : _bag(other._bag) {}

//set &set::operator=(const set &other) {
//	this->_bag = other._bag;
//	return *this;
//}

//set::~set() {}

//void set::insert(int val) {
//	if (!this->_bag->has(val))
//		this->_bag->insert(val);
//}

//void set::insert(int *array, int size) {
//	for (int i = 0; i < size; i++)
//		this->insert(array[i]);
//}

//void set::print() const {
//	this->_bag->print();
//}

//void set::clear() {
//	this->_bag->clear();
//}

//bool set::has(int val) const {
//	return this->_bag->has(val);
//}

//searchable_bag &set::get_bag() const {
//	return *this->_bag;
//}
