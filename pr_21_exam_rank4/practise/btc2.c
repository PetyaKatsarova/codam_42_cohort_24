#include <stdio.h>
#include <stdlib.h>

char *g_expr;

typedef struct s_node
{
    int             val;
    char            op;
    struct  s_node  *left;
    struct  s_node  *right;
} t_node;

static void skip_spaces()
{
    while (*g_expr == ' ')
        g_expr++;
}

t_node *create_node(int val, char op)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        return NULL;
    node->val = val;
    node->op = op;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_tree(t_node *node)
{
    if (!node)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

t_node *parse_plus_min();

int ft_is_digit(char bla)
{
    if (bla >= '0' && bla <= '9')
        return 1;
    return 0;
}

t_node *parse_num()
{
    int    val = 0;
    int     sign = 1;
    skip_spaces();
    if (*g_expr == '(')
    {
        g_expr++;
        t_node *sth = parse_plus_min();
        skip_spaces();
        if (*g_expr == ')')
            g_expr++;
        return sth;
    }
    if (*g_expr == '-')
    {
        sign = -1;
        g_expr++;
    }
    while (ft_is_digit(*g_expr))
    {
        val = val * 10 + (*g_expr - '0');
        g_expr++;
    }
    return (create_node(val * sign, 'N'));
}

t_node *parse_on_mult_dev()
{
    t_node *left = parse_num();
    skip_spaces();
    while (*g_expr == '*' || *g_expr == '/')
    {
        char op = *g_expr++;
        t_node *right = parse_num();
        t_node *node = create_node(0, op);
        node->left = left;
        node->right = right;
        left = node;
        skip_spaces();
    }
    return left;
}

t_node *parse_plus_min()
{
    t_node *left = parse_on_mult_dev();
    skip_spaces();
    while (*g_expr == '+' || *g_expr == '-')
    {
        char op = *g_expr++;
        t_node *right = parse_on_mult_dev();
        t_node *node = create_node(0, op);
        skip_spaces();
        node->left = left;
        node->right = right;
        left = node;
    }
    return left;
}

int calculate(t_node *root)
{
    if (!root)
        return 0;
    int left = calculate(root->left);
    int right = calculate(root->right);

    if (root->op == 'N')
        return root->val;
    if (root->op == '*')
        return left * right;
    if (root->op == '-')
        return left - right;
    if (root->op == '+')
        return left + right;
    if (root->op == '/')
    {
        if (right == 0)
        {
            printf("cant devide by 0\n");
            exit(1);
        }
        return left / right;
    }
    return 0;
}

int main(int argc, char **argv)
{
    printf("hello w :)\n");
    if (argc != 2)
        return (printf("add string with desired calculation: '1 + 2 * (3 -3) / 2"));   
    g_expr = argv[1]; // no validation done
    t_node *root = parse_plus_min();
    printf("result = %d\n", calculate(root));
    free_tree(root);
    return 0;
}