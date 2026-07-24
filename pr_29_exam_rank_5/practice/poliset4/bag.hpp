#ifndef BAG_HPP
#define BAG_HPP


/*
theory:
1. virtual on a function → about behavior (polymorphism):
class bag {
public:
    virtual void insert(int) = 0;   // pure virtual → bag is abstract
    virtual ~bag() {}
};
= 0 makes a function pure, and a class with at least one pure virtual function is abstract (can't be instantiated).

2. virtual in the inheritance list → about memory layout (the diamond):
class array_bag : virtual public bag { ... };
This has nothing to do with whether bag is abstract or has pure functions. It says: "if two branches of a hierarchy both contain bag, keep only one shared bag sub-object instead of two copies."
Virtual on inheritance solves exactly one problem: the same base class reachable through two+ paths, which would otherwise duplicate it. You add virtual to the middle classes, not the diamond's tip.

          bag (abstract: insert/print/clear are =0)
         / |  \
  arr_b tr_b searchable_bag (abstract: has()=0)

  array_bag, tree_bag, searchable_bag each do virtual public bag. Not because bag needs it alone — a single inheritance path never needs virtual —
  but because you know downstream classes will combine two of these branches.

  searchable_array_bag : virtual public array_bag, virtual public searchable_bag — here's the actual diamond: bag is reachable via array_bag→bag
  and via searchable_bag→bag. Since both parents already inherited bag virtually, searchable_array_bag gets one shared bag subobject instead of
  two ambiguous copies. searchable_tree_bag is the identical pattern with tree_bag swapped in.

!!NB!!
a class with any virtual function should have a virtual destructor. Once one destructor in the chain is virtual, all derived destructors are automatically virtual too — that's why array_bag's plain ~array_bag() would become virtual for free.

Diamond (two parents share a base) → the two parents inherit the base virtual public. That's the whole virtual-inheritance rule.
Deleting through a base pointer → that base needs virtual ~. In practice: put it on bag, the root, and everything below is covered.
*/
class bag
{
public:
	virtual void insert(int) = 0;
	virtual void insert(int *, int)  = 0;
	virtual void print() const = 0;
	virtual void clear() = 0;
};

#endif
