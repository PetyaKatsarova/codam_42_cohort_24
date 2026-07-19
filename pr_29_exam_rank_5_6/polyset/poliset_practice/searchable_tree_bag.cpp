#include "searchable_tree_bag.hpp"

bool searchable_tree_bag::has(int val) const {
    node *n = this->tree;
	while (n)
	{
        if (val == n->value)
            return true;
		if (val < (n)->value)
			n = (n)->l;
		else if (val >= n->value)
			n = (n)->r;
	}
    return false;
}