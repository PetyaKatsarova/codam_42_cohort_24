///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Allowed functions: pipe, fork, dup2, execvp, close, exit
write the following function:
    int    ft_popen(const char file, char const *argv[], char type)
The function must launch the executable file with the arguments argv (using execvp).
If the type is 'r' the function must return a file descriptor connected to the output of the command.
If the type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.
example:
int main() {
    int fd = ft_popen("ls", (char const[]){"ls", NULL}, 'r');
    charline;
    while(line = get_next_line(fd))
        ft_putstr(line);
}
Hint: Do not leak file descriptors! */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Assignment name:		vbc
// Expected files:		*.c *h
// Allowed functions:	malloc, calloc, realloc, free, printf, isdigit, write
// Write a program that prints the result of a mathematical expression given as argument.
// It must handle addition, multiplication and parenthesis. All values are between 0 and 9 included.
// In case of an unexpected symbol, you must print "Unexpected token '%c'\n".
// If the expression ends unexpectedly, you must print "Unexpected end of input\n".
// The same rule applies if finding an unexpected '(' or ')'.
// In case of a syscall failure, you must exit with 1.
// Examples:
// $> ./vbc '1' | cat -e
// 1$
// $> ./vbc '2+3' | cat -e
// 5$
// $> ./vbc '3*4+5' | cat -e
// 17$
// $> ./vbc '3+4*5' | cat -e
// 23$
// $> ./vbc '(3+4)*5' | cat -e
// 35$
// $> ./vbc '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' | cat -e
// 188$
// $> ./vbc '1+'
// Unexpected end of input
// $> ./vbc '1+2)' | cat -e
// Unexpected token ')'$
// File provided: vbc.c, see below.
//This file is given at the exam for vbc.c



#include <stdio.h>
#include <malloc.h>
#include <ctype.h>


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

static node *link_nodes(int type, node *l, node *r);
static node *parse_three(char **s);
static node *parse_two(char **s);
static node *parse_one(char **s);

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
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
        printf("Unexpected end of file\n");
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
    unexpected(**s);
    return (0);
}

// ----------------------------------------------------------------------------------------------- //
// ----------------------------------------------------------------------------------------------- //
// ----------------------------------------------------------------------------------------------- //
// ----------------------------------------------------------------------------------------------- //
// ----------------------------------------------------------------------------------------------- //

static node *link_nodes(int type, node *l, node *r) {
	

		if (!l || !r) {
			destroy_three(l);
			destroy_three(r);
			return NULL;
		}

		node n;
		n.type = type;
		n.val = 0;
		n.l = l;
		n.r = r;

		node *ret = new_node(n);
		if (!ret) {
			destroy_three(l);
			destroy_three(r);
			return NULL;
		}
		return ret;
}

static node *parse_three(char **s) {
	
	if (**s == '(') {

		(*s)++;
		node *inside = parse_one(s);
		if (!inside) {
			return NULL;
		}

		if (!expect(s, ')')) {
			destroy_three(inside);
			return NULL;
		}
		return inside;
	}
	if (isdigit(s)) {

		int v = **s - '0';
		(*s)++;
		node n;
		n.type = VAL;
		n.val = v;
		n.l = NULL;
		n.r = NULL;
		return new_node(n);
	}
	unexpected(**s);
	return NULL;
}

static node *parse_two(char **s) {

	node *left = parse_three(s);
	if (!left) 
		return NULL;

	while (accept(s, '*')) {

		node *right = parse_three(s);
		if (!right) { 
			destroy_three(left); 
			return NULL;
		};

		node *combine = link_nodes(MULTI, left, right);
		if (!combine) {
			destroy_tree(left);
			destroy_tree(right);
			return NULL;
		};

		left = combine;
	}
	return left;
}

static node *parse_one(char **s) {

	node *left = parse_two(s);
	if(!left) return NULL;

	while (accept(s, '+')) {
		node *right = parse_two(s);
		if (!right){ 
			destroy_tree(left); 
			return NULL;
		};

		node *combine = link_nodes(ADD, left, right);
		if (!combine) {
			destroy_tree(left);
			destroy_tree(right);
			return NULL;
		};

		left = combine;
	}
	return left;
}

// ----------------------------------------------------------------------------------------------- //
// ----------------------------------------------------------------------------------------------- //
// ----------------------------------------------------------------------------------------------- //
// ----------------------------------------------------------------------------------------------- //
// ----------------------------------------------------------------------------------------------- //


node *parse_exprt(char *s)
{
	char *p = *s;
	
	node *ret = parse_one(&p);
	if (!ret)
		return NULL;
	
	if (*p) {
		unexpected(*p);
		destrpy_tree(ret);
		return(NULL);
	}
	return ret;
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