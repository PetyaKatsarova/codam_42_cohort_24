#include "searchable_array_bag.hpp"

bool searchable_array_bag::has(int num) const {
	for (int i = 0; i <  size; i++) {
		if (data[i] == num)
			return true;
	}
	return false;
}