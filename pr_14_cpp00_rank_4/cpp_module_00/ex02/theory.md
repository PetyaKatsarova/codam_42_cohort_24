==========================================
typedef unsigned int uint;
Now uint means unsigned int.
==========================================
C++ Standard Library (STL) offers std::vector<T> = a dynamic array, like Java's ArrayList<T>.

Automatically resizes.
Stores elements in contiguous memory.
std::vector<int> nums = {1, 2, 3};
=========================================

typedef Account t;
This means:
Account::t is just another name for Account.
Like a self-alias.
So, Account::t == Account.

Why do that?
Often used to follow naming styles in C++ projects.
You can change the class name later without updating other code.
==========================================
typedef std::vector<Account::t> accounts_t;
Now we know:
Account::t == Account

So this means:
typedef std::vector<Account> accounts_t;
Which is:
An alias accounts_t for std::vector<Account>
===========================================
typedef	"make a nickname"
std::vector<T>	Dynamic array of T (like ArrayList in Java)
Account::t	A shortcut for Account
accounts_t	A shortcut for std::vector<Account>
==========================================
typedef std::pair<accounts_t::iterator, ints_t::iterator> acc_int_t;
Means:
“Create a new name acc_int_t for a pair of two iterators.”

 What is an iterator?
Think of it like a pointer that walks through a container (like vector, map, etc.).

In C:
int arr[] = {10, 20, 30};
int* p = arr;      // p points to first element
p++;

std::vector<int> v = {10, 20, 30};
std::vector<int>::iterator it = v.begin();  // points to first element
++it;
An iterator:

Works like a smart pointer
*it gives value
++it goes to next

Concept	Think of it as
iterator	smart pointer for containers
std::pair<A, B>	a box with two values
acc_int_t	a box with two iterators: one for vector<Account>, one for vector<int>
========================================
!!NB!!
========================================
 ++it → Prefix increment
Increments the iterator

Returns the new position

Faster and preferred in C++ when using iterators.

🔹 it++ → Postfix increment
Makes a copy of the iterator

Increments the original

Returns the old copy (before increment)

More expensive because of the copy.

++it	Better for iterators — no copy, faster
it++	Only use if you need the old value before incrementing
=========================================
!!NB!!

class Account {
    // no constructor or destructor defined
};
C++ automatically provides:
A default constructor: Account()
A default destructor: ~Account()

These:
Do nothing special
Just allocate and destroy memory

When should you define them?
Only if you need:
To initialize data (Account(int initial_deposit))
To clean up resources(files, sockets, memory, mutex, etc.)
To print messages (like ;created, ;closed in your example)

You can also tell C++ to generate them like this:

Account() = default;
~Account() = default;
===============================================
std::time_t now = std::time(nullptr);
Gets the current time as the number of seconds since Jan 1, 1970 (Unix epoch).

std::time(nullptr) means: "give me the time now".

std::tm* localTime = std::localtime(&now);
Converts those seconds (now) into readable time (year, month, day, hour, min, sec).

Returns a pointer to a std::tm struct:

struct tm {
	int tm_year;  // years since 1900
	int tm_mon;   // 0–11
	int tm_mday;  // day of month
	int tm_hour;  // 0–23
	int tm_min;
	int tm_sec;
	// ...
};

If now is: 1718554700 seconds since 1970,
std::localtime(&now) turns it into:

ini
Copy
Edit
tm_year = 125   (2025 = 1900 + 125)
tm_mon = 5      (June = 5 + 1)
tm_mday = 16
tm_hour = 17
tm_min = 58
tm_sec = 20
So it becomes: 2025-06-16 17:58:20

So you can print:
[20250616_175820]
===============================================
