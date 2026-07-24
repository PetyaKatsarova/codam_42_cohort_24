#ifndef SEARCHABLE_TREE_BAG_HPP
#define SEARCHABLE_TREE_BAG_HPP

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class Searchable_tree_bag : public tree_bag, public searchable_bag
{
public:
    Searchable_tree_bag();
    Searchable_tree_bag(const Searchable_tree_bag& copy);
    Searchable_tree_bag& operator=(const Searchable_tree_bag& assign);
    ~Searchable_tree_bag();

    virtual bool has(int value) const;
private:
	static bool search_node(node *curr, int item);
};

#endif