#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &other) : tree_bag(other) {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag &other){
	if (this != &other) {
		this->operator=(other);
	}
	return *this;
}

searchable_tree_bag::~searchable_tree_bag(){}


bool searchable_tree_bag::has(int num) const{
	node *n = tree;
	while (n) {
		if (n->value == num)
			return true;
		else if (n->value < num)
			n = n->r;
		else
			n = n->l;
	}
	return false;
}
