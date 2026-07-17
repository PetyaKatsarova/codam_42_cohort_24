#ifndef BAG_HPP
#define BAG_HPP


/*
theory:
1. virtual on a function → about behavior (polymorphism):
cppclass bag {
public:
    virtual void insert(int) = 0;   // pure virtual → bag is abstract
    virtual ~bag() {}
};
= 0 makes a function pure, and a class with at least one pure virtual function is abstract (can't be instantiated). That's the rule you remembered — but it's about functions, not inheritance.
2. virtual in the inheritance list → about memory layout (the diamond):
cppclass array_bag : virtual public bag { ... };
This has nothing to do with whether bag is abstract or has pure functions. It says: "if two branches of a hierarchy both contain bag, keep only one shared bag sub-object instead of two copies."
Without it, searchable_array_bag would contain two separate bags (one via array_bag, one via searchable_bag), and every mention of a bag member would be an ambiguity error.
Proof they're independent: you could have a diamond of completely non-abstract classes with zero virtual functions and still need virtual inheritance to merge the base. And conversely, an abstract class inherited through a single path needs no virtual inheritance at all.

here's no virtual class in C++ — the word only attaches to functions or to inheritance, never to the class itself. What you casually call a "virtual class" is either "abstract class" (has a pure virtual function) or "virtual base" (inherited virtually).

when do I need virtual inheritance?
Only when a diamond exists (or might exist): the same base reachable through two paths. Your rule at the end is exactly right: two classes inherit from the same base, and I inherit from both of them → those two classes must inherit the base with virtual public. The virtual goes on the middle classes (array_bag, searchable_bag), because they're the ones creating the duplicate paths. It's about memory layout, nothing else.

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
