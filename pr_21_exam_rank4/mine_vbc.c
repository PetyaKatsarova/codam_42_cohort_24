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

void errorprinter(char *msg, char token)
{
    printf("%s '%c'\n", msg, token);
    exit(1);
}

// Comprehensive input validation
int firstcheck(char *str)
{
    int c = 0, i = -1;

    if (str[0] != '(' && !isdigit(str[0]))
        errorprinter("Unexpected token", str[0]);
    
    while(str[++i])
    {
        // Check for invalid characters
        if (str[i] != '(' && str[i] != ')' && str[i] != '+' && str[i] != '*' && !isdigit(str[i]))
            errorprinter("Unexpected token", str[i]);
        
        // Check for consecutive operators
        if ((str[i] == '+' || str[i] == '*') && (str[i + 1] == '+' || str[i + 1] == '*'))
            errorprinter("Unexpected token", str[i + 1]);
        
        // Check for multi-digit numbers (not allowed)
        if (isdigit(str[i]) && isdigit(str[i + 1]))
            errorprinter("Unexpected token", str[i + 1]);
        
        // Check for operators after '('
        if (str[i] == '(' && (str[i + 1] == '+' || str[i + 1] == '*'))
            errorprinter("Unexpected token", str[i + 1]);
        
        // Check for operators before ')'
        if (str[i] == ')' && (str[i - 1] == '+' || str[i - 1] == '*'))
            errorprinter("Unexpected token", str[i - 1]);
        
        // Check for empty parentheses
        if (str[i] == '(' && str[i + 1] == ')')
            errorprinter("Unexpected token", str[i + 1]);
        
        // Count parentheses
        if (str[i] == '(')
            c++;
        if (str[i] == ')')
            c--;
        
        // Check for unmatched closing parenthesis
        if (c < 0)
            errorprinter("Unexpected token", ')');
    }
    
    // Check for unmatched opening parenthesis
    if (c > 0)
        errorprinter("Unexpected token", '(');
    
    // Check for unexpected end
    if (str[i - 1] != ')' && !isdigit(str[i - 1]))
    {
        printf("Unexpected end of input\n");
        exit(1);
    }
    
    // Handle single digit case
    if (isdigit(str[0]) && !str[1])
        return(str[0] - '0');
    
    return(0);
}

node *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        exit(1); // Syscall failure
    *ret = n;
    return (ret);
}

void destroy_tree(node *n)
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

// Simple parser (input already validated)
node *parse_expr(char *s);
node *parse_addition(char **s);
node *parse_multiplication(char **s);
node *parse_factor(char **s);

node *parse_factor(char **s)
{
    if (**s == '(')
    {
        (*s)++; // consume '('
        node *inside = parse_addition(s);
        (*s)++; // consume ')' (guaranteed to be there)
        return inside;
    }
    
    if (isdigit(**s))
    {
        node n = {VAL, **s - '0', NULL, NULL};
        (*s)++;
        return new_node(n);
    }
    
    return NULL; // Should never happen after validation
}

node *parse_multiplication(char **s)
{
    node *left = parse_factor(s);
    
    while (**s == '*')
    {
        (*s)++; // consume '*'
        node *right = parse_factor(s);
        node n = {MULTI, 0, left, right};
        left = new_node(n);
    }
    
    return left;
}

node *parse_addition(char **s)
{
    node *left = parse_multiplication(s);
    
    while (**s == '+')
    {
        (*s)++; // consume '+'
        node *right = parse_multiplication(s);
        node n = {ADD, 0, left, right};
        left = new_node(n);
    }
    
    return left;
}

node *parse_expr(char *s)
{
    char *p = s;
    return parse_addition(&p);
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

int main(int argc, char **argv)
{
    if (argc != 2)
        exit(1);
    
    int single_digit = firstcheck(argv[1]);
    if (single_digit > 0)
    {
        printf("%d\n", single_digit);
        return(0);
    }
    
    node *tree = parse_expr(argv[1]);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return(0);
}