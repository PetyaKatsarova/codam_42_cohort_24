#include "searchable_tree_bag.hpp"

Searchable_tree_bag::Searchable_tree_bag() : tree_bag() {}

Searchable_tree_bag::Searchable_tree_bag(const Searchable_tree_bag &copy)
	: tree_bag(copy) {}

Searchable_tree_bag &Searchable_tree_bag::operator=(const Searchable_tree_bag &assign) {
	if (this != &assign) {
		tree_bag::operator=(assign);
	}
	return *this;
}

Searchable_tree_bag::~Searchable_tree_bag() {}

bool Searchable_tree_bag::has(int value) const {
	 return search_node(tree, value);
}

bool Searchable_tree_bag::search_node(node *curr, int value) {
	if (curr == 0)
		return false;
	if (curr->value == value)
		return true;
	if (value < curr->value)
		return search_node(curr->l, value);
	else
		return search_node(curr->r, value);
}