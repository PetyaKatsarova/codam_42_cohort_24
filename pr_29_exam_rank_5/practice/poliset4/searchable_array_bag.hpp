#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP
#include "array_bag.hpp"
#include "searchable_bag.hpp"

/**
 * Since searchable_array_bag inherits from array_bag, it automatically inherits:

Constructor
Destructor
Copy constructor
Copy assignment operator
You only need to add the canonical form if:

You have member variables that need special handling
You need to override the inherited behavior
 */

class searchable_array_bag : virtual public searchable_bag, public array_bag {
	public:

		bool has(int) const;
};

#endif