#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}


searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other){}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& other) {
	tree_bag::operator=(other);
	return *this;
}

searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::has(int val) const{
	node *n = tree;

	while (n) {
		if (val == n->value)
			return true;
		else if (val < n->value)
			n = n->l;
		else
			n = n->r;
	}
	return false;
}

