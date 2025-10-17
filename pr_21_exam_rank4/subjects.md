PICOSHELL https://github.com/elinakly/exam42/blob/main/rank4/ft_popen.c
Allowed functions: pipe, fork, dup2, execvp, close, exit
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
Hint: Do not leak file descriptors!
========================================================

Assignment name:		vbc
Expected files:		*.c *h
Allowed functions:	malloc, calloc, realloc, free, printf, isdigit, write
Write a program that prints the result of a mathematical expression given as argument.
It must handle addition, multiplication and parenthesis. All values are between 0 and 9 included.
In case of an unexpected symbol, you must print "Unexpected token '%c'\n".
If the expression ends unexpectedly, you must print "Unexpected end of input\n".
The same rule applies if finding an unexpected '(' or ')'.
In case of a syscall failure, you must exit with 1.
Examples:
$> ./vbc '1' | cat -e
1$
$> ./vbc '2+3' | cat -e
5$
$> ./vbc '3*4+5' | cat -e
17$
$> ./vbc '3+4*5' | cat -e
23$
$> ./vbc '(3+4)*5' | cat -e
35$
$> ./vbc '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' | cat -e
188$
$> ./vbc '1+'
Unexpected end of input
$> ./vbc '1+2)' | cat -e
Unexpected token ')'$
File provided: vbc.c, see below.
// given code: 

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

node    *parse_expr(char *s)
{
    //...
    if (*s)
    {
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
================================================================

Assignment name  : sandbox
Expected files  : sandbox.c
Allowed functions : fork, waitpid, exit, alarm, sigaction, kill,
      printf, strsignal, errno

Write the following function:
#include <stdbool.h>
int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
This function must test if the function f is a nice function or a bad function,
you will return 1 if f is nice , 0 if f is bad or -1 in case of an error in
your function.
A function is considered bad if it is terminated or stopped by a signal
(segfault, abort...), if it exit with any other exit code than 0 or if it
times out.
If verbose is true, you must write the appropriate message among the following:
"Nice function!\n"
"Bad function: exited with code <exit_code>\n"
"Bad function: <signal description>\n"
"Bad function: timed out after <timeout> seconds\n"
You must not leak processes (even in zombie state, this will be checked using
wait).
We will test your code with very bad functions.
==================================================================

ft_popen
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
Hint: Do not leak file descriptors!
====================================================================

