#include "searchable_array_bag.hpp"

bool searchable_array_bag::has(int val) const {
	for (int i = 0; i < size; i++) {
		if (data[i] == val)
			return true;
	}
	return false;
}