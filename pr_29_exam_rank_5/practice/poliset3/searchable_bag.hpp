
#ifndef SEARCHABLE_HPP
#define SEARCHABLE_HPP
#include "bag.hpp"

/**
 * Abstract classes must have virtual destructor (for polymorphic deletion)
Optional: Can have other constructors/operators, but not required since can't be instantiated directly
 */
class searchable_bag : virtual public bag {
public:
	virtual ~searchable_bag() {};
	virtual bool has(int) const = 0;
};


#endif
