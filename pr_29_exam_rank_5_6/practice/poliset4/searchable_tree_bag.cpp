#include "searchable_tree_bag.hpp"

/**
 * Use when you need to point to an object's memory address
	Can be nullptr or reassigned
	Access members with -> or dereference with *

	Reference (&)
Use when you need an alias to an existing object
Cannot be null, must be initialized
Access members with . (like a regular variable)
Commonly used for function parameters to avoid copying
void func(const int& val);  // parameter by reference
int& getRef();              // return reference

None (Value)
Use when you want a copy of the object
Independent from the original
Changes don't affect the original

 */
bool searchable_tree_bag::has(int val) const {
	node *n = tree;

	while (n) {
		if (n->value == val)
			return true;
		else if(val < n->value)
			n = n->l;
		else
			n = n->r;
	}
	return false;
}