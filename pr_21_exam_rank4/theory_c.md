*s++ - Increment the pointer itself
cchar *str = "hello";
char **s = &str;

char c = *s++;  // What happens:
                // 1. Dereference s to get str
                // 2. Return current value of str
                // 3. Increment s (the double pointer)

Postfix ++ has higher precedence than *
Equivalent to: *(s++)
Moves the pointer s forward (the char**)

char *str = "hello";
char **s = &str;

char c = (*s)++;  // What happens:
                  // 1. Dereference s to get str
                  // 2. Return current char (*str)
                  // 3. Increment str (move to next char)

char *str = "abc";
char **s = &str;

// Using *s++
printf("%c\n", **s);   // 'a'
*s++;                  // s now points to... garbage! (next memory location)
printf("%c\n", **s);   // SEGFAULT or garbage

// Reset
str = "abc";
s = &str;

// Using (*s)++
printf("%c\n", **s);   // 'a'
(*s)++;                // str now points to 'b'
printf("%c\n", **s);   // 'b'
(*s)++;                // str now points to 'c'
printf("%c\n", **s);   // 'c'