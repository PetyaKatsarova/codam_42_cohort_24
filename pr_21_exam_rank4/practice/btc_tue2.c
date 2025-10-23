#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>


/**
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
    node *ret = calloc(1, sizeof(node));
    if (!ret)
        exit(1);
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

// prints out correct msg
void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

// return 1 if **s==c and (*s)++, else return 0
int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

// accept() and unexpected()
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
	return 0;
}

node *parse_num(char **s);
node *parse_multiply(char **s);
node *parse_add(char **s);

node *parse_num(char **s)
{
    if (**s == '(')
    { 
        (*s)++;
        node *bla = parse_add(s);
        if (!bla)
            return NULL;
        if (!expect(s, ')')) // prints err msg
            return (destroy_tree(bla), NULL);
        return bla;
    }
    if (isdigit(**s))
    {
        node n = {VAL, **s - '0', NULL, NULL};
        (*s)++;
        return (new_node(n));
    }
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
    if (!s || !*s)
        return NULL;
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