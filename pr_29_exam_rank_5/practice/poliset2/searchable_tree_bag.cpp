#include "searchable_tree_bag.hpp"

bool searchable_tree_bag::has(int num) const {
	node *const *n = &this->tree;
	while (*n) {
		if ((*n)->value == num)
			return true;
		if ((*n)->value > num)
			n = &(*n)->l;
		else if (num >= (*n)->value)
			n = &(*n)->r;
	}
	return false;
}

