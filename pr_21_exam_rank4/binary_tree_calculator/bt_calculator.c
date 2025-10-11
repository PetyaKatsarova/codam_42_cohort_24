#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> // isdigit()

typedef struct s_node
{
    char    op;
    int     val;
    struct  s_node *left;
    struct  s_node *right;
} t_node;

char *g_expr; // global, instead to pass s arg in funcs

t_node *create_node(char op, int val)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        return NULL;
    node->op = op;
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void skip_spaces(void)
{
    while (*g_expr == ' ')
        g_expr++;
}

t_node *parse_expr(void);

t_node *parse_num(void)
{
    int sign = 1;
    int val = 0;

    skip_spaces();
    if (*g_expr == '(')
    {
        g_expr++;
        t_node *node = parse_expr();
        if (!node)
        {
            // todo: protect, free
        }
        skip_spaces();
        if (*g_expr == ')')
            g_expr++;
        return node;
    }
    if (*g_expr == '-')
    {
        sign = -1;
        g_expr++;
    }
    while(isdigit(*g_expr))
    {
        val = val * 10 + (*g_expr - '0');
        g_expr++;
    }
    return create_node('N', sign * val);
}

t_node *parse_term(void)
{
    t_node *left = parse_num();
    skip_spaces();

    while (*g_expr == '*' || *g_expr == '/')
    {
        char op = *g_expr++; // returns first char, moves ++ pointer
        t_node *right = parse_num();
        t_node *node = create_node(op, 0);
        node->left = left;
        node->right = right;
        left = node;
        skip_spaces();
    }
    return left;
}

t_node *parse_expr(void)
{
    t_node *left = parse_term();
    skip_spaces();

    while (*g_expr == '+' || *g_expr == '-')
    {
        char op = *g_expr++;
        t_node *right = parse_term();
        t_node *node = create_node(op, 0);
        node->left = left;
        node->right = right;
        left = node;
        skip_spaces();
    }
    return left;
}

int evaluate(t_node *node)
{
    if (!node)
        return 0;
    if (node->op == 'N')
        return node->val;
    int left = evaluate(node->left);
    int right = evaluate(node->right);

    if (node->op == '+')
        return left + right;
    if (node->op == '-')
        return left - right;
    if (node->op == '*')
        return left * right;
    if (node->op == '/')
        return left / right;
    return 0;
}

void free_tree(t_node *node)
{
    if (!node)
        return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void print_tree_horizontal(t_node *node, char *prefix, int is_last)
{
    if (!node)
        return;
    printf("%s", prefix);
    printf("%s", is_last ? "└──" : "├──");
    if (node->op == 'N')
        printf("%d\n", node->val);
    else
        printf("%c\n", node->op);

    char new_prefix[256];
    // write to the char string str:
    sprintf(new_prefix, "%s%s", prefix, is_last ? "  " : "| ");
    if (node->left || node->right)
    {
        print_tree_horizontal(node->left, new_prefix, !node->right);
        print_tree_horizontal(node->right, new_prefix, 1);
    }
}

void print_tree(t_node *node, int depth, char prefix)
{
    // print root node
    if (!node)
        return;
    for (int i = 0; i < depth; i++)
        printf (" ");
    if (node->op == 'N')
        printf("%c%d\n", prefix, node->val);
    else
        printf("%c%c\n", prefix, node->op);

    // if children print:
    if (node->left || node->right)
    {
        if (node->left)
            print_tree(node->left, depth+1, 'L');
        else
        {
            for (int i = 0; i < depth + 1; i++)
                printf(" ");
            printf("L(null)\n");
        }

        if (node->right)
            print_tree(node->right, depth+1, 'R');
        else
        {
            for (int i = 0; i < depth +1; i++)
                printf(" ");
            printf("R(null)\n");
        }
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }
    g_expr = argv[1];
    t_node *root = parse_expr();

    if (!root)
    {
        printf("Error\n");
        return 1;
    }
    // print_tree(root, 0, ' ');
    print_tree_horizontal(root, "", 1);
    int result = evaluate(root);
    printf("%d\n", result);
    free_tree(root);
    return 0;
}
