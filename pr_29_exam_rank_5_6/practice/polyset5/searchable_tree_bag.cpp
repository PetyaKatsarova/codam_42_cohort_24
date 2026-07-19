#include "searchable_tree_bag.hpp"

bool searchable_tree_bag::has(int val) const {
	node* n = tree;

	while (n) {
		if (n->value == val)
			return true;
		else if (val < n->value)
			n = n->l;
		else
			n = n->r;
	}
	return false;
}