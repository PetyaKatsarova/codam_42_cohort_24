#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    int             val;
    char            op;
    struct  s_node *left;
    struct  s_node *right;
} t_node;

char *g_expr;

t_node *create_node(int val, char op)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
    {
        // do we need to protect?? todo better to exit here the app and free all??
        return NULL;
    }
    node->val = val;
    node->op = op;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_tree(t_node *root)
{
    if (!root)  return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void skip_spaces()
{
    while (*g_expr == ' ')
        g_expr++;
}

int ft_is_digit(char num)
{
    if (num >= '0' && num <= '9')
        return 1;
    return 0;
}

t_node *parse_on_plus_min();

t_node  *parse_num()
{
    int val = 0, sign = 1;
    
    skip_spaces();
    if (*g_expr == '(')
    {
        g_expr++;
        t_node *left = parse_on_plus_min();
        if (*g_expr == ')')
            g_expr++;
        return left; // no protection if () not closed
    }
    if (*g_expr == '-')
    {
        g_expr++;
        sign = -1;
    }
    while (ft_is_digit(*g_expr))
    {
        val = 10 * val + (*g_expr - '0');
        g_expr++;
    }
    return (create_node(val * sign, 'N')); // not operand
}

t_node *parse_on_mult_dev()
{
    t_node *left = parse_num();
    if (!left)
        return NULL;
    skip_spaces();
    while (*g_expr == '*' || *g_expr == '/')
    {
        char op = *g_expr++;
        t_node *right = parse_num();
        if (!right)
            return (free_tree(left), NULL);
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

t_node *parse_on_plus_min()
{
    t_node *left = parse_on_mult_dev();
    if (!left)
        return NULL;
    skip_spaces();
    while (*g_expr == '+' || *g_expr == '-')
    {
        char op = *g_expr++;
        t_node *right = parse_on_mult_dev();
        if (!right)
            return (free_tree(left), NULL);
        t_node *node = create_node(0, op);
        if (!node)
            return (free_tree(left), free_tree(right), NULL);
        skip_spaces();
        node->left = left;
        node->right = right;
        left = node;
    }
    return left;
}

int result (t_node *root)
{
    if (!root)
        return 0; // todo: lame
    if (root->op == 'N')
        return (root->val);
    int left = result(root->left);
    int right = result (root->right);
    
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
            free_tree(root);
            printf("naughty, naughty, cant devide by 0\n");
            exit(0);
        }
        return left / right;
    }
    return 0;
}

int main(int argc, char **argv)
{
    printf("lets calculate...\n");
    if (argc != 2)
        return(printf("naughty, naughty: enter param like '2 + 3 / 4 - (2*3)"), 1);
    g_expr = argv[1];
    t_node *root = parse_on_plus_min();
    printf("result = %d\n", result(root));
    free_tree(root);
    return 0;
}