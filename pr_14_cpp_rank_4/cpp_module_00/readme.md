-- SOLO abt 22 hrs

-- learning concepts --
Namespaces, classes, member functions, stdio streams,
initialization lists, static, const
-----------------------------------

• Write class names in UpperCamelCase format. Files containing class code will
always be named according to the class name. For instance:
ClassName.hpp/ClassName.h, ClassName.cpp, or ClassName.tpp. Then, if you
have a header file containing the definition of a class "BrickWall" standing for a
brick wall, its name will be BrickWall.hpp.

• You are allowed to use almost everything from the standard library. Thus, instead
of sticking to what you already know, it would be smart to use the C++-ish versions
of the C functions you are used to as much as possible.
• However, you can’t use any other external library. Boost libraries are forbidden. The following functions are forbidden too: *printf(), *alloc() and free().
• using namespace <ns_name> and
friend keywords are forbidden.
• You are allowed to use the STL only in Modules 08 and 09. That means:
no Containers (vector/list/map, and so forth) and no Algorithms (anything that
requires including the <algorithm> header) until then
• Memory leakage occurs in C++ too. When you allocate memory (by using the new
keyword), you must avoid memory leaks.
• From Module 02 to Module 09, your classes must be designed in the Orthodox
Canonical Form
• You should be able to use each of your headers independently from others. Thus,
they must include all the dependencies they need. However, you must avoid the
problem of double inclusion by adding include guards

================================================
** MODULE CPP 00 **
================================================
Exercise : 00
------------------------------------------------
Megaphone
Turn-in directory : ex00/
Files to turn in : Makefile, megaphone.cpp
Forbidden functions : None

write a program that produces the following output:
$>./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...
$>./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
$>./megaphone
* LOUD AND UNBEARABLE FEEDBACK NOISE *
$>
-----------------------------------------------