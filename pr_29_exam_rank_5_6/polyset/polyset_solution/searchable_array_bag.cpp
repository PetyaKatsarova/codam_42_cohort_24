#include "searchable_array_bag.hpp"

Searchable_array_bag::Searchable_array_bag() : array_bag() {}

Searchable_array_bag::Searchable_array_bag(const Searchable_array_bag &copy)
	: array_bag(copy) {}

Searchable_array_bag &Searchable_array_bag::operator=(const Searchable_array_bag &assign) {
	if (this != &assign) {
		array_bag::operator=(assign);
	}
	return *this;
}

Searchable_array_bag::~Searchable_array_bag() {}

bool Searchable_array_bag::has(int value) const {
	for (int i = 0; i < size; i++) {
		if (data[i] == value)
			return true;
	}
	return false;
}