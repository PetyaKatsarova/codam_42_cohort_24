#include "searchable_tree_bag.hpp"

bool searchable_tree_bag::has(int val) const {
	node *curr = tree;
	while (curr != nullptr) {
		if (curr->value == val)
			return true;
		if (curr->value > val)
			curr = curr->l;
		else
			curr = curr->r;	
	}
	return false;
}