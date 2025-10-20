#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    char            op;
    int             val;
    struct  s_node  *left;
    struct  s_node  *right;
} t_node;

char *g_expr = "";

t_node *create_node(int val, char op)
{
    t_node *n = malloc(sizeof(t_node));
    if (!n)
        return NULL;
    n->op = op;
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void free_tree(t_node *node)
{
    if (!node)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void skip_spaces()
{
     while (*g_expr == ' ')
        g_expr++;

}

int ft_is_digit(char bla)
{
    if (bla >= '0' && bla <= '9')
        return 1;
    return 0;
}

t_node *parse_on_plus_minus();

t_node *parse_num()
{
    int val = 0;
    int sign = 1;

    skip_spaces();
    if (*g_expr == '(')
    {
        g_expr++;
        t_node *node = parse_on_plus_minus();
        skip_spaces();
        if (*g_expr == ')')
            g_expr++; // again no protection: waht happens if wrong input: no ()? do protection: TODO
        return node;
    }
    if (*g_expr == '-')
    {
         sign = -1;
         g_expr++;
    }
    while (ft_is_digit(*g_expr))
    {
        val = 10 * val + (*g_expr - '0'); // no overflow protection done
        g_expr++;
    }
    return (create_node(val * sign, 'N'));
}

/**
parse_num is lowest level: creates a node from a leaf of the tree
parse_on_multipl_dev is second level: traverses the string and creates nodes on * || /
pares_on_plus_min is top level: traverses and creates nodes from right to left as a tree on + || -
*/
t_node *parse_on_multipl_dev()
{
    t_node *left = parse_num(); // creates new node or if in () returns node of op with left and right sides of values int
    skip_spaces();
    if (!left)
        return NULL;
    while (*g_expr == '*' || *g_expr == '/')
    {
        char op = *g_expr++;
        t_node *right = parse_num();
        if (!right)
        {
            free_tree(left);
            return NULL;
        }
        t_node *node = create_node(0, op);
        if (!node)
        {
            free_tree(left);
            free_tree(right);
            return NULL;
        }
        node->left = left;
        node->right = right;
        left = node;
        skip_spaces();
    }
    return left;
}

t_node *parse_on_plus_minus()
{
    t_node *left = parse_on_multipl_dev();
    if (!left)
        return NULL;
    while (*g_expr == '+' || *g_expr == '-')
    {
        char op = *g_expr++;
        t_node *right = parse_on_multipl_dev();
        if (!right)
        {
            free_tree(left);
            return NULL;
        }
        t_node *node = create_node(0, op);
        if (!node)
        {
            free_tree(left);
            free_tree(right);
            return NULL;
        }
        node->left = left;
        node->right = right;
        left = node;
        skip_spaces();
    }
    return left;
}

int evaluate(t_node *root)
{
    if (!root)
        return 0;
    if (root->op == 'N')
        return root->val;
    int left = evaluate(root->left);
    int right = evaluate(root->right);
    if (root->op == '+')
        return left + right;
    if (root->op == '-')
        return left - right;
    if (root->op == '*')
        return left * right;
    if (root->op == '/')
    {
        if (right == 0)
        {
            printf("cant / 0\n");
            free_tree(root);
            exit(1);
        }
        return left / right;
    }
    return 0;
}

void print_tree(t_node *root, char prefix, int level)
{
    if (!root)
        return;
    for (int i = 0; i < level; i++)
        printf(" ");
    if (level > 0)
        printf("%c: ", prefix);
    if (root->op == 'N')
        printf("%d\n", root->val);
    else
        printf("%c\n", root->op);
    if (root->left)
        print_tree(root->left, 'L', level + 1);
    if (root->right)
        print_tree(root->right, 'R', level + 1);
}

// ./a.out 2 + 3 * 4 - (2 * 4)"
int main(int argc, char **argv)
{   
    printf("hello w\n");
    if (argc != 2)
    {
        printf("wrong input, example: '2 + 3 * 4 - (2 * 4)'");
        return 1;                             
    }
    g_expr = argv[1];
    t_node *root = parse_on_plus_minus();
    printf("result = %d\n", evaluate(root));
    print_tree(root, ' ', 0);
    free_tree(root);
    return 0;
}