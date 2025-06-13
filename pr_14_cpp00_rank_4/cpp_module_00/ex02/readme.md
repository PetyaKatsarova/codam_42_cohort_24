Exercise : 02
The Job Of Your Dreams
Turn-in directory : ex02/
Files to turn in : Makefile, Account.cpp, Account.hpp, tests.cpp
Forbidden functions : None
Account.hpp, tests.cpp, and the log file are available for download
on the module’s intranet page.
Today is your first day at GlobalBanksters United. After successfully passing the recruitment tests (thanks to a few Microsoft Office tricks a friend showed you), you joined
the dev team. You also know the recruiter was amazed by how quickly you installed
Adobe Reader. That little extra made all the difference and helped you defeat all your
opponents (aka the other applicants): you made it!
Anyway, your manager just gave you some work to do. Your first task is to recreate a
lost file. Something went wrong and a source file was deleted by mistake. Unfortunately,
your colleagues don’t know what Git is and use USB keys to share code. At this point, it
would make sense to leave this place right now. However, you decide to stay. Challenge
accepted!
Your fellow developers give you a bunch of files. Compiling tests.cpp reveals that
the missing file is Account.cpp. Lucky you, the header file Account.hpp was saved.
There is also a log file. Maybe you could use it in order to understand how the Account
class was implemented.
9
C++ - Module 00
Namespaces, classes, member functions, stdio streams,
initialization lists, static, const, and some other basic stuff

You start to recreate the Account.cpp file. In only a few minutes, you code a few
lines of pure awesome C++. After a couple of failed compilations, your program passes
the tests. Its output matches perfectly the one saved in the log file (except for the
timestamps which will obviously differ since the tests saved in the log file were run
before you were hired).
Damn, you’re impressive!
The order in which the destructors are called may differ depending on
your compiler/operating system. So your destructors may be called in
a reverse order.
Completing exercise 02 is not mandatory to pass this module.