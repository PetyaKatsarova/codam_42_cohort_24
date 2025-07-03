C++ - Module 03
Inheritance

C++ - Module 03 Inheritance
• Note that unless explicitly stated otherwise, the using namespace <ns_name> and
friend keywords are forbidden. Otherwise, your grade will be -42.
• You are allowed to use the STL only in Modules 08 and 09. That means:
no Containers (vector/list/map, and so forth) and no Algorithms (anything that
requires including the <algorithm> header) until then. Otherwise, your grade will
be -42.
A few design requirements
• Memory leakage occurs in C++ too. When you allocate memory (by using the new
keyword), you must avoid memory leaks.
• From Module 02 to Module 09, your classes must be designed in the Orthodox
Canonical Form, except when explicitly stated otherwise.
• Any function implementation put in a header file (except for function templates)
means 0 to the exercise.
• You should be able to use each of your headers independently from others. Thus,
they must include all the dependencies they need. However, you must avoid the
problem of double inclusion by adding include guards. Otherwise, your grade will
be 0.
Read me
• You can add some additional files if you need to (i.e., to split your code). As these
assignments are not verified by a program, feel free to do so as long as you turn in
the mandatory files.
• Sometimes, the guidelines of an exercise look short but the examples can show
requirements that are not explicitly written in the instructions.
• Read each module completely before starting! Really, do it.
• By Odin, by Thor! Use your brain!!!
Regarding the Makefile for C++ projects, the same rules as in C apply
(see the Norm chapter about the Makefile).
You will have to implement a lot of classes. This can seem tedious,
unless you’re able to script your favorite text editor.
4
C++ - Module 03 Inheritance
You are given a certain amount of freedom to complete the exercises.
However, follow the mandatory rules and don’t be lazy. You would
miss a lot of useful information! Do not hesitate to read about
theoretical concepts.
--------------- ex00 -------------------------
Turn-in directory : ex00/
Files to turn in : Makefile, main.cpp, ClapTrap.{h, hpp}, ClapTrap.cpp
Forbidden functions : None
First, you have to implement a class!
It will be called ClapTrap and will have the following private attributes initialized
to the values specified in brackets:
• Name, which is passed as a parameter to the constructor
• Hit points (10), representing the health of the ClapTrap
• Energy points (10)
• Attack damage (0)
Add the following public member functions so that the ClapTrap behaves more realistically:
• void attack(const std::string& target);
• void takeDamage(unsigned int amount);
• void beRepaired(unsigned int amount);
When ClapTrap attacks, it causes its target to lose <attack damage> hit points.
When ClapTrap repairs itself, it regains <amount> hit points. Attacking and repairing
each cost 1 energy point. Of course, ClapTrap can’t do anything if it has no hit points or
energy points left. However, since these exercises serve as an introduction, the ClapTrap
instances should not interact directly with one another, and the parameters will not refer
to another instance of ClapTrap.
6
C++ - Module 03 Inheritance
In all of these member functions, you need to print a message to describe what happens. For example, the attack() function may display something like (of course, without
the angle brackets):
ClapTrap <name> attacks <target>, causing <damage> points of damage!
The constructors and destructor must also display a message, so your peer-evaluators
can easily see that they have been called.
Implement and turn in your own tests to ensure your code works as expected.
7
Chapter IV
Exercise 01: Serena, my love!
Exercise : 01
Serena, my love!
Turn-in directory : ex01/
Files to turn in : Files from the previous exercise + ScavTrap.{h, hpp},
ScavTrap.cpp
Forbidden functions : None
Because you can never have enough ClapTraps, you will now create a derived robot.
It will be named ScavTrap and will inherit the constructors and destructor from ClapTrap. However, its constructors, destructor, and attack() will print different messages.
After all, ClapTraps are aware of their individuality.
Note that proper construction/destruction chaining must be shown in your tests.
When a ScavTrap is created, the program starts by constructing a ClapTrap. Destruction occurs in reverse order. Why?
ScavTrap will use the attributes of ClapTrap (update ClapTrap accordingly) and
must initialize them to:
• Name, which is passed as a parameter to the constructor
• Hit points (100), representing the health of the ClapTrap
• Energy points (50)
• Attack damage (20)
ScavTrap will also have its own special ability:
void guardGate();
This member function will display a message indicating that ScavTrap is now in Gate keeper mode.
Don’t forget to add more tests to your program.
8
Chapter V
Exercise 02: Repetitive work
Exercise : 02
Repetitive work
Turn-in directory : ex02/
Files to turn in : Files from previous exercises + FragTrap.{h, hpp},
FragTrap.cpp
Forbidden functions : None
Making ClapTraps is probably starting to get on your nerves.
Now, implement a FragTrap class that inherits from ClapTrap. It is very similar to
ScavTrap. However, its construction and destruction messages must be different. Proper
construction/destruction chaining must be shown in your tests. When a FragTrap is created, the program starts by constructing a ClapTrap. Destruction occurs in reverse order.
Same goes for the attributes, but with different values this time:
• Name, which is passed as a parameter to the constructor
• Hit points (100), representing the health of the ClapTrap
• Energy points (100)
• Attack damage (30)
FragTrap has a special ability too:
void highFivesGuys(void);
This member function displays a positive high-fives request on the standard output.
Again, add more tests to your program.
9
Chapter VI
Exercise 03: Now it’s weird!
Exercise : 03
Now it’s weird!
Turn-in directory : ex03/
Files to turn in : Files from previous exercises + DiamondTrap.{h, hpp},
DiamondTrap.cpp
Forbidden functions : None
In this exercise, you will create a monster: a ClapTrap that’s half FragTrap, half ScavTrap. It will be named DiamondTrap, and it will inherit from both FragTrap AND
ScavTrap. This is so risky!
The DiamondTrap class will have a private attribute named name. This attribute must
have exactly the same variable name as in the ClapTrap base class (without referring to
the robot’s name).
To be clearer, here are two examples:
If ClapTrap’s variable is name, give the DiamondTrap’s variable the name name.
If ClapTrap’s variable is _name, give the DiamondTrap’s variable the name _name.
Its attributes and member functions will be inherited from its parent classes:
• Name, which is passed as a parameter to a constructor
• ClapTrap::name (parameter of the constructor + "_clap_name" suffix)
• Hit points (FragTrap)
• Energy points (ScavTrap)
• Attack damage (FragTrap)
• attack() (ScavTrap)
10
C++ - Module 03 Inheritance
In addition to the special functions from both parent classes, DiamondTrap will have
its own special ability:
void whoAmI();
This member function will display both its name and its ClapTrap name.
Of course, the ClapTrap instance of DiamondTrap will be created once, and only once.
Yes, there’s a trick.
Again, add more tests to your program.
Do you know the -Wshadow and -Wno-shadow compiler flags?
You can pass this module without completing exercise 03.
