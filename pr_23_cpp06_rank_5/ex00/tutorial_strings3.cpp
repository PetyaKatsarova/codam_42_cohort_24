#include <iostream>
#include <string>

/**
init and mem alloc
c_str() convert string object to c
str.insert(indexAtInt, "str appends before first original char");
append(), assing(), insert(), erase(), replace(), substr()-> like c strstr(0, 5) // from index 0 get 5 chars
*/

/**
str.erase(pos, len); // rmv len chars starting at pos
str.erase(pos); // rmv from pos to end
str.erase(iterator); // rmv signle char at iterator
str.erase(begin_it, end_it); // rmv range [begin, end)
str.erase() return reference to itself, can chain operations:
str.erase(0, 5).erase(2,3).append("!");
*/

static void eraseBla(std::string bla) {
    
}

int main() {
    std::string s1 = "Hi";
    std::string s2 = "World";
    
    printf("+: %s\n", (s1+s2).c_str());
    s1+= " there";
    std::cout << "s1+=" << s1 << "\n";

    s1.append(", friend"); // always only at the end
    s1.append(3, '!'); // append ! 3 times
    printf("s1.append()=%s\n", s1.c_str());

    s1 = "New str";
    printf("s1 reassing: %s\n", s1.c_str()); // new str
    s1.assign("Another str"); 
    printf(".assign(%s)\n", s1.c_str()); // another str
    // Insert
    s1.insert(0, "Start: "); // b4 first char
    s1.insert(s1.end(), '!'); // at end: like append
    std::cout << "insert: " << s1 << "\n";

    std::string s5 = s1.erase(0, 7); // rmv from index 0 7 chars
   printf("erased 7 chars from s1[%s], s5[%s]\n", s1.c_str(), s5.c_str()); // erased Start:
    //std::cout << "s5[" << s5 << "] erased s1[" << s1 << "]\n";
   // s1.erase(s1.begin() + 5); // at pos 5 rmv 1 char
    //std::cout << "erases 1char:" << s1 << "\n";

    return 0;
}