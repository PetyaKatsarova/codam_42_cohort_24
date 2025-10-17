// //vbc 
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

// [8:27 AM] //This file is given at the exam for vbc.c   <--------- Important

// #include <stdio.h>
// #include <malloc.h>
// #include <ctype.h>
// typedef struct node {
//     enum {
//         ADD,
//         MULTI,
//         VAL
//     }   type;
//     int val;
//     struct node *l;
//     struct node *r;
// }   node;
// node    *new_node(node n)
// {
//     node *ret = calloc(1, sizeof(n));
//     if (!ret)
//         return (NULL);
//     *ret = n;
//     return (ret);
// }
// void    destroy_tree(node *n)
// {
//     if (!n)
//         return ;
//     if (n->type != VAL)
//     {
//         destroy_tree(n->l);
//         destroy_tree(n->r);
//     }
//     free(n);
// }
// void    unexpected(char c)
// {
//     if (c)
//         printf("Unexpected token '%c'\n", c);
//     else
//         printf("Unexpected end of file\n");
// }
// int accept(char **s, char c)
// {
//     if (**s)
//     {
//         (*s)++;
//         return (1);
//     }
//     return (0);
// }
// int expect(char **s, char c)
// {
//     if (accept(s, c))
//         return (1);
//     unexpected(**s);
//     return (0);
// }
// //...
// node    *parse_expr(char *s)
// {
//     //...
//     if (*s)
//     {
//         destroy_tree(ret);
//         return (NULL);
//     }
//     return (ret);
// }
// int eval_tree(node *tree)
// {
//     switch (tree->type)
//     {
//         case ADD:
//             return (eval_tree(tree->l) + eval_tree(tree->r));
//         case MULTI:
//             return (eval_tree(tree->l) * eval_tree(tree->r));
//         case VAL:
//             return (tree->val);
//     }
	
// }
// int main(int argc, char **argv)
// {
//     if (argc != 2)
//         return (1);
//     node *tree = parse_expr(argv[1]);
//     if (!tree)
//         return (1);
//     printf("%d\n", eval_tree(tree));
//     destroy_tree(tree);
// }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Salution
// #include <stdlib.h>
// #include <ctype.h>
// #include <stdio.h>
// #include <malloc.h>


// static node *link_nodes(int type, node *l, node *r) {
	

// 		if (!l || !r) {
// 			destroy_three(l);
// 			destroy_three(r);
// 			return NULL;
// 		}

// 		node n;
// 		n.type = type;
// 		n.val = 0;
// 		n.l = l;
// 		n.r = r;

// 		onde *ret = new_node(n);
// 		if (!ret) {
// 			destroy_three(l);
// 			destroy_three(r);
// 			return NULL;
// 		}
// 		return ret;
// }

// static node *parse_three(char **s) {
	
// 	if (**s == '(') {

// 		(*s)++;
// 		node *inside = parse_one(s);
// 		if (!inside) {
// 			return NULL;
// 		}

// 		if (!expect(s, ')')) {
// 			destroy_three(inside);
// 			return NULL;
// 		}
// 		return inside;
// 	}
// 	if (isdigit(s)) {

// 		int v = **s - '0';
// 		(*s)++;
// 		node n;
// 		n.type = VAL;
// 		n.val = v;
// 		n.l = NULL;
// 		n.r = NULL;
// 		return new_node(n);
// 	}
// 	unexpected(**s);
// 	return NULL;
// }

// static node *parse_two(char **s) {

// 	node *left = parse_three(s);
// 	if (!left) return NULL;

// 	while (accept(s, '*')) {

// 		node *right = parse_three(s);
// 		if (!right) { 
// 			destroy_three(left); 
// 			return NULL;
// 		};

// 		node *combine = link_nodes(MULTI, left, right);
// 		if (!combine) {
// 			destroy_tree(left);
// 			destroy_tree(right);
// 			return NULL;
// 		};

// 		left = combine;
// 	}
// 	return left;
// }

// static node *parse_one(char **s) {

// 	node *left = parse_two(s);
// 	if(!left) return NULL;

// 	while (accept(s, '+')) {
// 		node *right = parse_two(s);
// 		if (!right){ 
// 			destroy_tree(left); 
// 			return NULL;
// 		};

// 		node *combine = link_nodes(ADD, left, right)
// 		if (!combine) {
// 			destroy_tree(left);
// 			destroy_tree(right);
// 			return NULL;
// 		};

// 		left = combine;
// 	}
// 	return left;
// }


// node *parse_exprt(char *s)
// {
// 	char *p = *s;
// 	node *ret = parse_level_one(&p);
// 	if (!ret)
// 		return NULL;
		
// 	if (*p){
// 		unexpected(*p);
// 		destrpy_tree(res);
// 		return(NULL);
// 	}
// 	return ret;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Assignment name:    picoshell
Expected files:        picoshell.c
Allowed functions:    close, fork, wait, exit, execvp, dup2, pipe
___
Write the following function:
int    picoshell(char **cmds[]);
The goal of this function is to execute a pipeline. It must execute each
commands [sic] of cmds and connect the output of one to the input of the
next command (just like a shell).
Cmds contains a null-terminated list of valid commands. Each rows [sic]
of cmds are an argv array directly usable for a call to execvp. The first
arguments [sic] of each command is the command name or path and can be passed
directly as the first argument of execvp.
If any error occur [sic], The function must return 1 (you must of course
close all the open fds before). otherwise the function must wait all child
processes and return 0. You will find in this directory a file main.c which
contain [sic] something to help you test your function.
Examples:
./picoshell /bin/ls "|" /usr/bin/grep picoshell
picoshell
./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'
squblblb/
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// // picoshell

// #include <unistd.h>
// #include <stddef.h>
// #include <sys/wait.h>


// int picoshell(char **cmds[]) {

// 	int i = 0;
// 	int n = 0;
// 	int children = 0;
// 	int prev = -1;
// 	int fd[2];
// 	pid_t pid;

// 	if (!cmds || !cmds[0])
// 		return 1;
	
// 	while (cmds[i++])
// 		n++;
	
// 	if (n == 0)
// 		return 1;

// 	for (i = 0; i < n ; i++) {
		
// 		if (i < n - 1) {
// 			pipe(fd);
// 			//protect
// 		}

// 		pid = fork();
// 		if (pid < 0) {
// 			if (i < n - 1) {
// 				close(fd[0]);
// 				close(fd[1]);
// 			}
// 			if (prev != -1)
// 				close(prev);
// 			while (children-- > 0)
// 				wait(NULL);
// 		}

// 		if (pid == 0) {

// 			if (prev != -1) {
// 				if (dup2(prev, 0) == -1) {
// 					// protect

// 					_exit(1);
// 				}
// 			}

// 			if (i < n - 1) {
// 				if (dup2(fd[1], 1) == -1) {
// 					//protect
// 					_exit(1);
// 				}
// 			}

// 			if (prev != -1)
// 				close(prev);

// 			if (i < n - 1) {
// 				close(fd[0]);
// 				close(fd[1]);
// 			}

// 			execvp(cmds[i][0], cmds[i]);
// 			_exit(1);
// 		}
// 		children++;

// 		if (prev != -1) {
// 			close(prev);
// 		}

// 		if (i < n - 1) {
// 			close(fd[1]);
// 			prev = fd[0];
// 		} else {
// 			prev = -1;
// 		}


// 	}

// 	if (prev != -1)
// 		close(prev);
	
// 	while (children-- > 0)
// 		wait(NULL);

// 	return 0;
// }


// // sandbox
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Assignment name  : sandbox
Expected files  : sandbox.c
Allowed functions : fork, waitpid, exit, alarm, sigaction, kill,
      printf, strsignal, errno
===============================================================================
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
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <string.h>
// #include <signal.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <errno.h>

// static void no_alarm(int signo) {
// 	(void)signo;
// }

// int sandbox(void (*f)(void), unsigned int timeout, bool verbose) {

// 	if (!f) {
// 		errno = EINVAL;
// 		return -1;
// 	}

// 	struct sigaction sa = {0};
// 	sa.sa_handler = no_alarm;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;

// 	if (sigaction(SIGALRM, sa, NULL) == -1) {
// 		return -1;
// 	}

// 	pid_t pid = fork();
// 	if (pid < 0)
// 		return -1;

// 	if (pid == 0) {
// 		f();
// 		_exit(0);
// 	}

// 	if (timeout > 0)
// 		alarm(timeout);
// 	else 
// 		alarm(0);

// 	int status;
// 	for(;;) {
// 		pid_t w = waitpid(pid, &status, 0);
// 		if (w == -1) {

// 			if (errno == EINTR) {

// 				unsigned int rem = alarm(0);

// 				if (timeout > 0 && rem == 0) {

// 					(void)kill(pid, SIGKILL);
// 					while()
// 					if (verbose) {
// 						printf();
// 					}
// 					return -1;
// 				}
// 				if (timeout > 0 && rem == > 0) {
// 					alarm(rem)
// 				}
// 				continue;
// 			}
// 			int save = errno;
// 			(void)kill(pid, SIGKILL);
// 			while(waitpid(pid, &status, 0) == -1 && errno == EINTR) {}
// 			errno = save;
// 			return -1;
// 		}

// 		if (WIFEXITED(status)) {
// 			int e = WEXITSTATUS(status);
// 			alarm(0);
// 			if (e == 0) {
// 				if (verbose) {
// 					printf();
// 				}
// 				return 1;
// 			}
// 			if (e > 0) {
// 				if (verbose) {
// 					printf();
// 				}
// 				return 0;
// 			}
// 		}

// 		if (WIFSIGNALED(status)) {
// 			int s = WTERMSIG(status);
// 			alarm(0);

// 			if (verbose) {
// 				const char *des = strsignal(s);
// 				if (!s) {
// 					des = "Unknown signal";
// 				}
// 				printf("%s\n",des);
// 			}
// 			return 0;
// 		}

// 		if (WIFSTOPPED(status)) {
// 			int so = WSTOPSIG(status);
// 			if (verbose) {

// 				const char *des = strsignal(so);
// 				if (!des) {
// 					des = "Unknown signal";
// 				}
// 				printf("Bad function: %s",des);
// 			}
// 			(void)kill(pid, SIGKILL);
// 			while(waitpid(pid, &status, 0) == -1 && errno == EINTR) {}
// 			alarm(0);
// 			return -1;
// 		}
// 	}
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // ft_popen
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


// #include <unistd.h>
// #include <sys/wait.h>

// // ft_popen

// int	ft_popen(const char *file, char const *argv[], char type)
// {
// 	int	fd[2];
// 	pid_t	pid;

// 	if (!file || !argv | !argv[0])
// 		return (-1);
// 	if (type != 'r' && type != 'w')
// 		return (-1);
// 	if (pipe(fd) == -1)
// 		return (-1);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
// 		return (-1);
// 	}
// 	if (pid == 0)
// 	{
// 		if (type == 'r')
// 		{
// 			if (dup2(fd[1], 1) == -1)
// 			{
// 				close(fd[0]);
// 				close(fd[1]);
// 				_exit(-1);
// 			}
// 		}
// 		else
// 		{
// 			if ((dup2(fd[0], 0) == -1))
// 			{
// 				close(fd[0]);
// 				close(fd[1]);
// 				_exit(-1);
// 			}
// 			close(fd[0]);
// 			close(fd[1]);
// 		}
// 		execvp(file, (char *const *)argv);
// 		_exit(127);
// 	}
// 	if (type == 'r')
// 	{
// 		close(fd[1]);
// 		return (fd[0]);
// 	}
// 	else
// 	{
// 		close(fd[0]);
// 		return (fd[1]);
// 	}
// 	return (-1);
// }


