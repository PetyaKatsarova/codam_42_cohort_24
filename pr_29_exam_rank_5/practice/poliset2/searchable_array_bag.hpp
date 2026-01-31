#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP
#include "searchable_bag.hpp"
#include "array_bag.hpp"

class searchable_array_bag : virtual public searchable_bag, public array_bag {
public:
	bool has(int) const;
};


#endif