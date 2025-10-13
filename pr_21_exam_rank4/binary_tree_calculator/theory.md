!!!! NB !!!!!!

g_expr++

Moves the pointer forward
Returns old pointer value
Doesn't dereference

char *g_expr = "abc";
g_expr++;  // Now g_expr points to "bc"

*g_expr++

Dereferences current character
Then moves pointer forward
Returns the character value

char *g_expr = "abc";
char c = *g_expr++;  // c = 'a', g_expr now points to "bc"
=====================================================================
Memory trick:

LEFT = what comes BEFORE the operator
RIGHT = what comes AFTER the operator
In 3 + 5:

3 goes LEFT of +
5 goes RIGHT of +


Operators = parents (have children)
Numbers = leaves (no children)
Left/Right = your view looking at the paper
Evaluation = start from bottom, work up
Precedence = *,/ before +,-
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
  ======================================================================
   Always from the TOP! 👑
We ALWAYS start with the KING (parse_on_plus_minus())
Why? Because + and - have the lowest precedence, so they should be at the TOP of the tree!