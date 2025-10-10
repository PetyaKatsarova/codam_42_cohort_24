!!!! NB !!!!!!

g_expr++

Moves the pointer forward
Returns old pointer value
Doesn't dereference

cchar *g_expr = "abc";
g_expr++;  // Now g_expr points to "bc"

*g_expr++

Dereferences current character
Then moves pointer forward
Returns the character value

cchar *g_expr = "abc";
char c = *g_expr++;  // c = 'a', g_expr now points to "bc"
=====================================================================



A binary tree is a hierarchical data structure where each node has at most 2 children (left and right).


For mathematical expressions, operators are internal nodes, numbers are leaf nodes:
Expression: (3+5)*10

Tree:
      *
     / \
    +   10
   / \
  3   5