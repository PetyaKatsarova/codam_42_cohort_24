#ifndef SEARHCABLEARRAYBAG_HPP
#define SEARHCABLEARRAYBAG_HPP

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class Searchable_array_bag : public array_bag, public searchable_bag {
	public:
			Searchable_array_bag();
			Searchable_array_bag(const Searchable_array_bag &copy);
			Searchable_array_bag &operator=(const Searchable_array_bag &assign);
			~Searchable_array_bag();

			virtual bool has(int value) const;
};

#endif