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

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

// returns 1 if **s==c
int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

node *parse_num(char **s);
node *parse_multiply(char **s);
node *parse_add(char **s);

node *parse_num(char **s)
{
    node *n = NULL;

    if (**s == '(')
    {
        (*s)++;
        n = parse_add(s);
        if (!n)
            return NULL;
        if (!expect(s, ')')) // prints unexpected if **s != ) and (*s)++
            return (destroy_tree(n), NULL);
        return n;
    }
    if (isdigit(**s))
    {
        node new = {VAL, **s - '0', NULL, NULL};
        (*s)++;
        return (new_node(new));
    }
    unexpected(**s);
    return NULL;
}

node *parse_multiply(char **s)
{
    node *left = parse_num(s);
    if (!left)
        return NULL;
    while (accept(s, '*'))
    {
        node *right = parse_num(s);
        if (!right)
        {
            destroy_tree(left);
            return NULL;
        }
        node n = {MULTI, 0, left, right};
        left = new_node(n);
    }
    return left;
}

node *parse_add(char **s)
{
    node *left = parse_multiply(s);
    if (!left)
        return NULL;
    while (accept(s, '+'))
    {
        node *right = parse_multiply(s);
        if (!right)
        {
            destroy_tree(left);
            return NULL;
        }
        node n = {ADD, 0, left, right};
        left = new_node(n);
    }
    return left;
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