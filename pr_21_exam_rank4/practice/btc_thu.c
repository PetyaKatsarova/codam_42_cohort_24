/**
Assignment name:		vbc
Expected files:		*.c *h
Allowed functions:	malloc, calloc, realloc, free, printf, isdigit, write
Write a program that prints the result of a mathematical expression given as argument.
It must handle addition, multiplication and parenthesis. All values are between 0 and 9 included.
In case of an unexpected symbol, you must print "Unexpected token '%c'\n".
If the expression ends unexpectedly, you must print "Unexpected end of input\n".
The same rule applies if finding an unexpected '(' or ')'.
In case of a syscall failure, you must exit with 1.
Examples:
$> ./a.out '1' | cat -e
1$
$> ./a.out '2+3' | cat -e
5$
$> ./a.out '3*4+5' | cat -e
17$
$> ./a.out '3+4*5' | cat -e
23$
$> ./a.out '(3+4)*5' | cat -e
35$
$> ./a.out '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' | cat -e
188$
$> ./a.out '1+'
Unexpected end of input
$> ./a.out '1+2)' | cat -e
Unexpected token ')'$
*/

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>


typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        exit(1); // syscall failure?
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

// if **s==c return 1, else print unexpected, return 0
int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
	//return 0;
}

node *parse_num(char **str);
node *parse_multiply(char **str);
node *parse_add(char **str);

node *parse_num(char **str)
{
	if (**str == '(')
	{
		(*str)++;
		node *bla = parse_add(str);
		if (!bla)
			return NULL;
		if (!expect(str, ')')) // if == 0 print unexpected
			return (destroy_tree(bla), NULL);
		return bla;
	}
	if (isdigit(**str))
	{
		node n = {VAL, **str - '0', NULL, NULL};
		(*str)++;
		return new_node(n);
	}
	unexpected(**str);
	return NULL;
}

node *parse_multiply(char **str)
{
	node *left = parse_num(str);
	if (!left)
		return NULL;
	while (accept(str, '*'))
	{
		node *right = parse_num(str);
		if (!right)
			return (destroy_tree(left), NULL);
		node n = {MULTI, 0, left, right};
		left = new_node(n);
	}
	return left;
}

node *parse_add(char **str)
{
	node *left = parse_multiply(str);
	if (!left)
		return NULL;
	while (accept(str, '+'))
	{
		node *right = parse_multiply(str);
		if (!right)
			return (destroy_tree(left), NULL);
		node n = {ADD, 0, left, right};
		left = new_node(n);
	}
	return left;
}


node    *parse_expr(char *s)
{
    node *ret = parse_add(&s);
	if (!ret)
		return NULL;
    if (*s)
    {
		unexpected(*s);
        destroy_tree(ret);
        return (NULL);
    }
    return (ret);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    node *tree = parse_expr(argv[1]);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
}
	