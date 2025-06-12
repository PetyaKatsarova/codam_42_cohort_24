
#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <array>
#include <iostream>
#include "Contact.hpp"


/**
 * array of contacts.
◦ maximum of 8 contacts. If the user tries to add a 9th contact,
replace the oldest one by the new one: first?
At program start-up, the phonebook is empty and the user is prompted to enter one
of three commands. The program only accepts ADD, SEARCH and EXIT.
 */
class PhoneBook {
	private:
	    Contact contacts[8];
		int 	nextIndex;
		int		allContacts;

	public:
		PhoneBook();
		void addContact();
		void searchContact() const;
};

#endif