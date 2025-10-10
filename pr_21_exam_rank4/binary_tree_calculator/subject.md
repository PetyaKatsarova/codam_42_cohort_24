Assignment name  : tree_calc
Expected files   : tree_calc.c
Allowed functions: malloc, free, atoi, printf, write
--------------------------------------------------------------------------------

Write a program that takes a mathematical expression as argument and evaluates it.

The expression contains:
- Numbers (integers)
- Operators: + - * / ( )
- Proper operator precedence (* / before + -)
- Parentheses for grouping

Implementation requirements:
- Parse the expression into a binary tree
- Each node is either:
  - Operator node (has left and right child)
  - Number node (leaf, no children)
- Evaluate the tree recursively

Example:
$> ./tree_calc "(3+5)*10"
80
$> ./tree_calc "2+3*4"
14
$> ./tree_calc "10/2-3"
2
$> ./tree_calc "(1+2)*(3+4)"
21

If the expression is invalid or wrong number of arguments, print "Error\n"