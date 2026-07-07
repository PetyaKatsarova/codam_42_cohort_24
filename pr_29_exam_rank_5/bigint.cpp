Host-specific information ====================================================
$> hostname; uname -msr
f1r1s16.codam.nl
Linux 5.15.0-163-generic x86_64
$> date
wo  4 feb 2026 12:11:26 CET

= User files collection ========================================================
Collecting user files from Vogsphere
Repository URL: git@vogsphere-v2.codam.nl:exam-2026-02-04/pekatsar_exam-rank-02_exam_13h41m34s.git

= Git history ==================================================================
$> git -C /tmp/tmp3w9v3szm/user log --pretty='%H - %an, %ad : %s'
586b69027919e54652404323fc404253f814c933 - Exam 42, Wed Feb 4 12:11:04 2026 +0100 : lost cause
972b23d79fdcbff836c99ee4d910191ec11ccb6a - Exam 42, Wed Feb 4 11:55:48 2026 +0100 : annoying
 
= Collected files ==========================================
$> ls -lAR /tmp/tmp3w9v3szm/user
/tmp/tmp3w9v3szm/user:
total 8
drwxr-xr-x 2 root root 4096 feb  4 12:11 bigint
-rw-r--r-- 1 root root  751 feb  4 12:11 __GIT_HISTORY

/tmp/tmp3w9v3szm/user/bigint:
total 16
-rw-r--r-- 1 root root  375 feb  4 12:11 bigint.cpp
-rw-r--r-- 1 root root  444 feb  4 12:11 bigint.hpp
-rw-r--r-- 1 root root 2048 feb  4 12:11 main.cpp
-rw-r--r-- 1 root root  981 feb  4 12:11 subject.en.txt
 
= bigint =======================================================================
$> c++ -std=c++98 bigint.cpp main.cpp -o user_exe 
In file included from bigint.cpp:1:
./bigint.hpp:21:19: error: 'this' argument to member function 'get_num' has type 'const bigint', but function is not marked const
    return (os << obj.get_num());
                  ^~~
./bigint.hpp:17:23: note: 'get_num' declared here
        unsigned int& get_num();        
                      ^
1 error generated.
In file included from main.cpp:1:
./bigint.hpp:21:19: error: 'this' argument to member function 'get_num' has type 'const bigint', but function is not marked const
    return (os << obj.get_num());
                  ^~~
./bigint.hpp:17:23: note: 'get_num' declared here
        unsigned int& get_num();        
                      ^
main.cpp:15:31: error: invalid operands to binary expression ('const bigint' and 'bigint')
        std::cout << "a + b = " << a + b << std::endl;
                                   ~ ^ ~
main.cpp:16:31: error: invalid operands to binary expression ('const bigint' and 'bigint')
        std::cout << "a + c = " << a + c << std::endl;
                                   ~ ^ ~
main.cpp:17:35: error: no viable overloaded '+='
        std::cout << "(c += a) = " << (c += a) << std::endl;
                                       ~ ^  ~
main.cpp:19:27: error: cannot increment value of type 'bigint'
        std::cout << "++b = " << ++b << std::endl;
                                 ^ ~
main.cpp:20:28: error: cannot increment value of type 'bigint'
        std::cout << "b++ = " << b++ << std::endl;
                                 ~^
main.cpp:21:41: error: invalid operands to binary expression ('bigint' and 'int')
        std::cout << "(b << 10) + 42 = " << (b << 10) + 42 << std::endl;
                                             ~ ^  ~~
./bigint.hpp:20:15: note: candidate function not viable: no known conversion from 'bigint' to 'std::ostream &' (aka 'basic_ostream<char> &') for 1st argument
std::ostream& operator<<(std::ostream &os, const bigint& obj) {
              ^
main.cpp:22:36: error: no viable overloaded '<<='
        std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
                                        ~ ^   ~
main.cpp:23:36: error: no viable overloaded '>>='
        std::cout << "(d >>= 2) = " << (d >>= 2) << std::endl;
                                        ~ ^   ~
main.cpp:26:34: error: invalid operands to binary expression ('bigint' and 'const bigint')
        std::cout << "(d < a) = " << (d < a) << std::endl;
                                      ~ ^ ~
main.cpp:27:34: error: invalid operands to binary expression ('bigint' and 'const bigint')
        std::cout << "(d > a) = " << (d > a) << std::endl;
                                      ~ ^ ~
main.cpp:28:35: error: invalid operands to binary expression ('bigint' and 'const bigint')
        std::cout << "(d == a) = " << (d == a) << std::endl;
                                       ~ ^  ~
main.cpp:29:35: error: invalid operands to binary expression ('bigint' and 'const bigint')
        std::cout << "(d != a) = " << (d != a) << std::endl;
                                       ~ ^  ~
main.cpp:30:35: error: invalid operands to binary expression ('bigint' and 'const bigint')
        std::cout << "(d <= a) = " << (d <= a) << std::endl;
                                       ~ ^  ~
main.cpp:31:35: error: invalid operands to binary expression ('bigint' and 'const bigint')
        std::cout << "(d >= a) = " << (d >= a) << std::endl;
                                       ~ ^  ~
main.cpp:33:4: error: no viable overloaded '='
        c = 0;
        ~ ^ ~
./bigint.hpp:14:23: note: candidate function not viable: no known conversion from 'int' to 'bigint &' for 1st argument
        const bigint& operator=(bigint& other);
                      ^
main.cpp:37:5: error: no viable overloaded '<<='
                c <<= 2;
                ~ ^   ~
main.cpp:38:5: error: no viable overloaded '+='
                c += 99;
                ~ ^  ~~
main.cpp:42:15: error: cannot increment value of type 'bigint'
        std::cout << ++c << std::endl;
                     ^ ~
fatal error: too many errors emitted, stopping now [-ferror-limit=]
20 errors generated.

Could not compile 'user_exe'
Grade: 0