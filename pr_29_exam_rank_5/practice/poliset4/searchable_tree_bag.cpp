#include "searchable_tree_bag.hpp"

bool searchable_tree_bag::has(int num) const {
	node *n = this->tree;
	while (n)
	{
		if (num == n->value)
			return true;
		if (num < (n)->value)
			n = (n)->l;
		else
			n = (n)->r;
	}
	return false;
}