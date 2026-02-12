#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include <cstdlib>
#include <iostream>
#include "set.hpp"


// c++ tree_bag.cpp searchable_tree_bag.cpp searchable_array_bag.cpp array_bag.cpp main.cpp
int main(int ac, char **av)
{
	if (ac == 1)
		return 1;
	searchable_bag *t = new searchable_tree_bag;
	searchable_bag *a = new searchable_array_bag;
	for (int i = 1; i < ac; i++)
	{
		t->insert(atoi(av[i]));
		a->insert(atoi(av[i]));
	}
	t->print();
	a->print();
	for (int i = 1; i < ac; i++)
	{
		std::cout << t->has(atoi(av[i])) << std::endl;
		std::cout << a->has(atoi(av[i])) << std::endl;
		std::cout << t->has(atoi(av[i]) - 1) << std::endl;
		std::cout << a->has(atoi(av[i]) - 1) << std::endl;
	}
	t->clear();
	a->clear();
	const searchable_array_bag tmp(dynamic_cast<searchable_array_bag &>(*a));
	tmp.print();
	tmp.has(1);
	set sa(*a);
	set st(*a);
	for (int i = 1; i < ac; i++)
	{
		st.insert(atoi(av[i]));
		sa.insert(atoi(av[i]));
	}
	sa.has(atoi(av[1]));
	sa.print();
	sa.get_bag().print();
	st.print();
	sa.clear();
 	int arr[] = {1, 2, 3, 4,};
	sa.insert(arr, 4);
	delete a;
	delete t;
}

// Here's how wikipedia define sets and bags:

// In computer science, a set is an abstract data type that can store unique
// values, without any particular order. It is a computer implementation of
// the mathematical concept of a finite set. Unlike most other collection
// types, rather than retrieving a specific element from a set, one typically
// tests a value for membership in a set.

// A generalization of the notion of a set is that of a multiset or bag,
// which is similar to a set but allows repeated ("equal") values (duplicates).
// This is used in two distinct senses: either equal values are considered
// identical, and are simply counted, or equal values are considered
// equivalent, and are stored as distinct items.

// Assignment name  : polyset
// Expected files   : searchable_array_bag.cpp, searchable_array_bag.hpp,
// searchable_tree_bag.cpp, searchable_tree_bag.hpp, set.cpp, set.hpp
// --------------------------------------------------------------------------------

// In this directory, you will find various classes:
//  - bag: an abstract class representing a bag.
//  - searchable_bag: an abstract class representing a bag with the ability to
//  search within it.
//  - array_bag: an implementation of a bag using an array as the underlying data structure.
//  - tree_bag: an implementation of a bag using a binary search tree as the underlying data structure.

// If you don't know what a set or a bag is, you can read the attached file:
// sets_and_bags.en.txt

// #### First part ####

// Since a bag without a searching function is not very useful, implement two
// classes, searchable_array_bag and searchable_tree_bag, that will inherit from
// array_bag and tree_bag, respectively, and implement the searchable_bag abstract
// class.

// #### Second part ####

// Implement the class set that will wrap a searchable_bag and turn it into a set.

// In this directory, you will find a main file that must compile with your code.

// All your classes should follow the orthodox canonical form.
// Don't forget the consts.

// The optimization of your code is not important in this exercise.

// This exercise has to comply with the C++98 standard.