#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other) {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag &other){
	if (this != &other)
		tree_bag::operator=(other);
	return *this;
}

searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::has(int num) const {
	node *bla = tree;
	while (bla) {
		if (bla->value == num)
			return true;
		else if (num > bla->value)
			bla = bla->r;
		else
			bla = bla->l;
	}
	return false;
}

