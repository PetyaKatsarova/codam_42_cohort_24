
BSP stands for Binary Space Partitioning

Imagine you have a triangle drawn on a piece of paper. Now, take a ruler and place it along one side of the triangle. That side acts like a wall, splitting the paper into two parts: one part is “inside” the triangle, and the other part is “outside.”

Do this for all three sides:

Each side of the triangle is like a wall that divides the space into “inside” and “outside.”
If you put a small sticker (your point) somewhere on the paper, you can check for each wall: is the sticker on the “inside” part or the “outside” part?
If the sticker is on the “inside” part for all three walls, then it’s inside the triangle!
If it’s on the “outside” for even one wall, it’s not inside the triangle.
So, BSP for a triangle is like using the triangle’s sides as walls to see if your sticker is in the special area that’s “inside” all the walls at once. If yes, it’s inside the triangle!
======================================
C++ uses a convenient abstraction called streams to perform input and output operations in sequential media such as the screen, the keyboard or a file. A stream is an entity where a program can either insert or extract characters to/from. streams are a source/destination of characters, and that these characters are provided/accepted sequentially (i.e., one after another).
======================================
The endl manipulator produces a newline character, exactly as the insertion of '\n' does; but it also has an additional behavior: the stream's buffer (if any) is flushed, which means that the output is requested to be physically written to the device, if it wasn't already. This affects mainly fully buffered streams, and cout is (generally) not a fully buffered stream. Still, it is generally a good idea to use endl only when flushing the stream would be a feature and '\n' when it would not. Bear in mind that a flushing operation incurs a certain overhead, and on some devices it may produce a delay.
=======================================
In most program environments, the standard input by default is the keyboard, and the C++ stream object defined to access it is cin.
#include <iostream>
using namespace std;

int main ()
{
  int i;
  cout << "Please enter an integer value: ";
  cin >> i;
  cout << "The value you entered is " << i;
  cout << " and its double is " << i*2 << ".\n";
  return 0;
}
==============================
The extraction operator can be used on cin to get strings of characters in the same way as with fundamental data types:

1
2
string mystring;
cin >> mystring;

However, cin extraction always considers spaces (whitespaces, tabs, new-line...) as terminating the value being extracted, and thus extracting a string means to always extract a single word, not a phrase or an entire sentence.

To get an entire line from cin, there exists a function, called getline, that takes the stream (cin) as first argument, and the string variable as second. For example:
// cin with strings
#include <iostream>
#include <string>
using namespace std;

int main ()
{
  string mystr;
  cout << "What's your name? ";
  getline (cin, mystr);
  cout << "Hello " << mystr << ".\n";
  cout << "What is your favorite team? ";
  getline (cin, mystr);
  cout << "I like " << mystr << " too!\n";
  return 0;
}