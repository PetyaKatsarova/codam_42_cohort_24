expected completion time 50hrs

https://github.com/vfurmane/pipex-tester

Program name pipex
Turn in files Makefile, *.h, *.c
Makefile NAME, all, clean, fclean, re
Arguments file1 cmd1 cmd2 file2
------------------------------------------------------------------
External functs.
• open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
• ft_printf and any equivalent
YOU coded
Libft authorized Yes
-------------------------------------------------------------------
Description This project is about handling pipes.
Your program will be executed as follows:
./pipex file1 cmd1 cmd2 file2
It must take 4 arguments:
• file1 and file2 are file names.
• cmd1 and cmd2 are shell commands with their parameters.
It must behave exactly the same as the shell command below:
$> < file1 cmd1 | cmd2 > file2
5
Pipex
III.1 Examples
$> ./pipex infile "ls -l" "wc -l" outfile
Should behave like: < infile ls -l | wc -l > outfile
$> ./pipex infile "grep a1" "wc -w" outfile
Should behave like: < infile grep a1 | wc -w > outfile
III.2 Requirements
Your project must comply with the following rules:
• You have to turn in a Makefile which will compile your source files. It must not
relink.
• You have to handle errors thoroughly. In no way your program should quit unex-
pectedly (segmentation fault, bus error, double free, and so forth).
• Your program mustn’t have memory leaks.
• If you have any doubt, handle the errors like the shell command:
< file1 cmd1 | cmd2 > file2
6

Bonus part
You will get extra points if you:
• Handle multiple pipes.
This:
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Should behave like:
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
• Support « and » when the first parameter is "here_doc".
This:
$> ./pipex here_doc LIMITER cmd cmd1 file
Should behave like:
cmd << LIMITER | cmd1 >> file


// ooops: not working in some built in commands cases:
./pipex main.c "cd ~" "pwd" tralala.md
./pipex main.c "export bla=tralala" "echo $bla" tralala.md

this works:
./pipex main.c "false" "echo $?" tralala.md
./pipex main.c "env" "echo $HOME" tralala.md