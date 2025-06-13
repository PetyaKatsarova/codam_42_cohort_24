
#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <array>
#include <iostream>
#include "Contact.hpp"


/**
 * array of contacts.
◦ store a maximum of 8 contacts in a circular buffer, overwriting the oldest contact once the limit is reached
At program start-up, the phonebook is empty and the user is prompted to enter one of three commands. The program only accepts ADD, SEARCH and EXIT.
 */
class PhoneBook {
	private:
	    Contact contacts[8]; // TODO: REVERT TO 8 FOR EVAL
		int 	contactIndex;
		int		allContacts;

	public:
		PhoneBook();
		void addContact();
		void searchContact() const;
};

#endif