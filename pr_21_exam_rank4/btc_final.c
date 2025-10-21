#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * doesnt handle space, binary tree calculator: like ((2+2*(3*3))*3+42)
 * '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' | cat -e
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
    node *res = calloc(1, sizeof(n));
    if (!res)
        exit(1);
    *res = n;
    return (res);
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
        printf("Unexpected end of input\n");  // Fix: "input" not "file"
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

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    return (unexpected(**s), 0);
}

// not really needed: done in practice/btc_tue.c
int validate_input(char *str)
{
    int c = 0, i = -1;

    if (str[0] != '(' && !isdigit(str[0]))
        return (unexpected(str[0]), -1);
	    // Handle single digit case
    if (isdigit(str[0]) && !str[1])
        return(str[0] - '0');
    while(str[++i])
    {
        if (str[i] != '(' && str[i] != ')' && str[i] != '+' && str[i] != '*' && !isdigit(str[i]))
			return (unexpected(str[i]), -1); 
        if ((str[i] == '+' || str[i] == '*') && (str[i + 1] == '+' || str[i + 1] == '*'))
			return (unexpected(str[i]), -1); // conseq. operators
        if (isdigit(str[i]) && isdigit(str[i + 1]))
			return (unexpected(str[i]), -1); // multidigit not allowed
        if (str[i] == '(' && (str[i + 1] == '+' || str[i + 1] == '*'))
			return (unexpected(str[i + 1]), -1); // operator after (
        if (str[i] == ')' && i > 0 && (str[i - 1] == '+' || str[i - 1] == '*'))
			return (unexpected(str[i + 1]), -1); // operator b4 )
        if (str[i] == '(' && str[i + 1] == ')')
			return (unexpected(str[i + 1]), -1); // empty parenthesis
        
        if (str[i] == '(')
            c++;
        if (str[i] == ')')
            c--;
        if (c < 0)  // unmatched closing parenthesis
            return ( unexpected(')'), -1);
    }
    if (c > 0)
        return (unexpected('('), -1);
    // Check for unexpected end i-1 is the char b4 the \0
    if (i > 0 && str[i - 1] != ')' && !isdigit(str[i - 1]))
        return (unexpected(0), -1);  
    return(0);  // Multi-character expression, needs parsing
}


node *parse_addition(char **s);
node *parse_multiplication(char **s);
node *parse_num(char **s);

node *parse_num(char **s)
{
    if (**s == '(')
    {
        (*s)++; // consume '('
        node *inside = parse_addition(s);
        if (!inside)
            return NULL;
        if (!expect(s, ')'))
        {
            destroy_tree(inside);
            return NULL;
        }
        return inside;
    }
    
    if (isdigit(**s))
    {
        node n = {VAL, **s - '0', NULL, NULL};
        (*s)++;
        return new_node(n);
    }
    
    unexpected(**s);
    return NULL;
}

node *parse_multiplication(char **s)
{
    node *left = parse_num(s);
    if (!left)
        return NULL;
    
    while (accept(s, '*'))
    {
        node *right = parse_num(s);
        if (!right)
            return (destroy_tree(left), NULL);
        node n = {MULTI, 0, left, right};
        left = new_node(n);
    }
    return left;
}

node *parse_addition(char **s)
{
    node *left = parse_multiplication(s);
    if (!left)
        return NULL;
    
    while (accept(s, '+'))
    {
        node *right = parse_multiplication(s);
        if (!right)
            return (destroy_tree(left), NULL);
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
    char *p = s;
    node *ret = parse_addition(&p);
    
    if (!ret)
        return NULL;
    
    if (*p)
    {
        unexpected(*p);
        destroy_tree(ret);
        return (NULL);
    }
    return (ret);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    int single_digit = validate_input(argv[1]);
    if (single_digit == -1)  // Validation error
        return (1);
    if (single_digit > 0)    // Single digit case
        return ( printf("%d\n", single_digit), 0);
    
    // Parse and evaluate expression
    node *tree = parse_expr(argv[1]);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return (0);
}
