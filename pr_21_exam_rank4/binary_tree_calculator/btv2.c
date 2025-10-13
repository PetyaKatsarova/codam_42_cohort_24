#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *g_expr = 0;

typedef struct s_node
{
    char            op;
    int             val;
    struct s_node  *left;
    struct s_node  *right;
}   t_node;

t_node *create_node(char op, int val)
{
    t_node *node;
    node = malloc(sizeof(t_node));
    if (!node)
        return NULL;
    node->op = op;
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void skip_spaces()
{
    while (*g_expr == ' ')
        g_expr++;
}

t_node *parse_on_plus_minus();

t_node *parse_num()
{
    int sign = 1;
    int val = 0;

    skip_spaces();
    if (*g_expr == '(')
    {
        g_expr++;
        t_node *node = parse_on_plus_minus();
        skip_spaces();
        if (*g_expr == ')')
            g_expr++;
        return node;
    }
    if (*g_expr == '-')
        sign = -1;
    while (isdigit(*g_expr))
    {
        val = 10 * val + (*g_expr - '0');
        g_expr++;
    }
    return create_node('N', sign * val);
}

t_node *parse_on_multipl_dev();

t_node *parse_on_plus_minus()
{
    t_node *left = parse_on_multipl_dev();
    skip_spaces();
    while (*g_expr == '+' || *g_expr == '-')
    {
        char op = *g_expr++;
        t_node *right = parse_on_multipl_dev();
        t_node *node = create_node(op, 0);
        node->left = left;
        node->right = right;
        left = node;
        skip_spaces();
    }
    return left;
}

t_node *parse_on_multipl_dev()
{
    t_node *left = parse_num();
    skip_spaces();

    while (*g_expr == '*' || *g_expr == '/')
    {
        char op = *g_expr++;
        t_node *right = parse_num();
        t_node *node = create_node(op, 0);
        node->left = left;
        node->right = right;
        left = node;
        skip_spaces();
    }
    return left;
}

void print_tree(t_node *node, int depth, char prefix)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++)
        printf(" ");
    if (depth > 0)
        printf("%c: ", prefix);
    if (node->op == 'N')
        printf("%d\n", node->val);
    else
        printf("%c\n", node->op);
    if (node->left)
        print_tree(node->left, depth + 1, 'L');
    if (node->right)
        print_tree(node->right, depth + 1, 'R');
}

void free_tree(t_node *node)
{
    if (!node)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void evaluate()
{
    
}

// ./a.out  "3 + 2*3 - 1 + 2"
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("wrong input: 'your expressionn");
    }
    g_expr = argv[1];
    t_node *root = parse_on_plus_minus();
    printf("trala la, calc %s\n", g_expr);
    print_tree(root, 0, 'Z');
    free_tree(root);
    return (0);
}