#include <string>
#include <iostream>
#include <cstring> // for strcpy and all c style manip

/**
c style, we included <cstring>
const char* cstr: a ptr to 1 or more const chars(c - style string), char it points to cant be modified, pointer to where it points can be modified
*/
int main() {
    const char* str1 = "Hello"; // literal: cant be modified even if not const; pointer to read only
    char str2[] = "hello"; // arr: can be modified, size automatically calculated (6 bytes includeing )
    char str3[20] = "world"; // remaining bytes init to 0
    char str4[6] = {'h', 'e', 'l', 'l', 'o', '\0'}; // must include \0

    // wrong, cant modify
    // char* str5 = "bla"; //warning in cpp11
   // str5[0] = 'B'; // crash: cant modify read only

    char str6[] = "bla";
    str6[0] = 'B';
    std::cout << "str6 value     : " << str6 << "\n";
    std::cout << "str6 first char: " << *str6 << std::endl;

    char str7[50]; // contains garbage values

    char *heapStr = new char[100];
    strcpy(heapStr, "Dynamic string");
    std::cout << "heapStr: " << heapStr << std::endl;
    // must free mem:
    delete[] heapStr;

    char* cStr = (char*)malloc(100 * sizeof(char));
    strcpy(cStr, "C-style alloc:");
    std::cout << "cStr char 0: " << *cStr << "\n"; 
    free(cStr);

    // common operations
    char src[] = "Hello";
    char dest[20];

    strcpy(dest, src); // copy
    strcat(dest, " World"); // concat: add
    int len = strlen(dest); // 11
    int cmp = strcmp(dest, src); // return > 0
    char *found = strstr(dest, "World"); //find substr

    printf("dest+cat: %s\nstrlen: %d\ncmp %d\nfound World: %s\n", dest, len, cmp, found);




    return 0;
}