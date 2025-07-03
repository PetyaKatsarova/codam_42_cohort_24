class Animal {
public:
    void eat() {
        std::cout << "Eating\n";
    }
};

class Dog : public Animal {
public:
    void bark() {
        std::cout << "Barking\n";
    }
};
===================
ClapTrap::ClapTrap(const std::string& n)
 What are the parts?
std::string → the type (a string object from the standard library)

& → reference

const → you promise not to modify it

n → the name of the parameter

What happens without &?
ClapTrap(std::string n)
❌ This makes a full copy of the string.
→ More memory used.
→ Slower (especially with big strings).

 Why use const std::string&?
ClapTrap(const std::string& n)
 & avoids copying → it refers to the original string.

 const makes sure you don't change it inside the function.

 Fast and safe.

 For dummies: What is a reference (&)?
It's like a nickname for a variable.

Instead of copying the whole string, you just point to the original.

 Analogy:

Passing by value (no &):   I make a photocopy of a book for you.
Passing by reference (&):  I give you the book to look at (but don’t change it)
=======================================================
ScavTrap scavyCopy(scavy);
It means:
You create a new object (scavyCopy)

You copy the values from scavy into scavyCopy

You do not affect scavy at all.

Does the original (scavy) get used?
Yes, but only read-only:

The copy constructor reads from scavy to get its values.

But it does not change scavy.

You borrow someone's recipe (copy), but you don’t touch their original paper.

ScavTrap scavy("Scavy");
ScavTrap scavyCopy(scavy);

scavyCopy.attack("CopyTarget");
scavy.attack("OriginalTarget");
scavy and scavyCopy both start with the same values.

You can modify them independently — one’s change doesn’t affect the other.
