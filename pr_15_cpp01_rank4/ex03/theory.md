You don’t have to write a constructor or destructor by hand in C++—the compiler will auto-generate:

A default constructor (Zombie()) that zero-inits or default-inits each member.

A copy constructor, copy-assignment, and a destructor (~Zombie()) that simply calls each member’s destructor.

But as soon as you declare any constructor (e.g. Zombie(const std::string&)), the compiler stops providing its own default constructor. Likewise, if you need to run custom code on construction (e.g. a log message) or destruction (cleanup), you must explicitly declare and define:

cpp
Copy
Edit
class Zombie {
public:
  Zombie();                    // default ctor
  Zombie(const std::string&);  // our custom ctor
  ~Zombie();                   // our custom dtor
  // ...
};