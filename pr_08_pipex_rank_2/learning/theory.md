man -k <keyword> (or apropos) to search all sections:
man -k printf

https://42-cursus.gitbook.io/guide/rank-02/pipex/understand-pipex
https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901

* see all active prcesses on unix*/
ps -e

/* any process id: */
pidof systemd //systemd is the init system responsible for starting and managing services and processes on most modern Linux systems.

pidof pidof //The pidof command is also a process while it is running

 we can check both the PID and PPID of the shell program in our terminal with the following command:

$ echo "PID = $$; PPID = $PPID"

=== ALLOWED FUNCS ===

perror: Prints an error message to stderr based on errno.
perror("Error");

strerror: Converts errno values into human-readable error strings.
char *msg = strerror(errno);

access: Checks a file's existence or permissions.
access("file.txt", F_OK);

dup: Duplicates a file descriptor.
int new_fd = dup(fd);

dup2: Duplicates a file descriptor to a specific value.
dup2(fd, STDOUT_FILENO);

execve: Replaces the current process with a new program.
execve("/bin/ls", args, env);

exit: Terminates a process with a status code.
exit(0);

fork: Creates a new process (child).
pid_t pid = fork();

pipe: Creates a pair of connected file descriptors for interprocess communication.
int pipe_fd[2];
pipe(pipe_fd);

unlink: Deletes a file.
unlink("file.txt");

wait: Waits for a child process to terminate.
wait(NULL);

waitpid: Waits for a specific child process to terminate.
waitpid(pid, NULL, 0);
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);

The wait call will retrieve the first terminated child, whereas waitpid holds out for the child matching the PID that we indicated and ignores all of the others. Also, waitpid allows us to specify a few options.
status: a pointer to an integer type variable in which wait and waitpid can store the child’s exit status. We will be able to examine this number with different macros to determine if the child finished normally or was interrupted, among other things.

=================== FORK ============================================

    When fork() is called, it creates a new process (child process) by duplicating the calling process (parent process).
    The new process gets a unique process ID (PID).

Returns Different Values in Parent and Child:

    In the parent process: fork() returns the PID of the child process.
    In the child process: fork() returns 0.
    If fork() fails (e.g., resource limit): It returns -1.

Asynchronous Execution:

    After the fork(), both the parent and child processes run concurrently and asynchronously.
    The exact order of execution is not guaranteed. Either the parent or the child might run first.
    ------------------------------------

int access(const char *pathname, int mode);
access() checks whether the program can access the file pathname. 

The mode specifies the accessibility check(s) to be performed, and is either the value F_OK, or a mask consisting of the bitwise OR of one or more of R_OK, W_OK, and X_OK. F_OK tests for the existence of the file. R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.

On success (all requested permissions granted), zero is returned. On error (at least one bit in mode asked for a permission that is denied, or some other error occurred), -1 is returned, and errno is set appropriately.
---------------------------------------------------------------------------

int dup2(int oldfd, int newfd);

dup2() makes newfd be the copy of oldfd, closing newfd first if necessary, but note the following:

    If oldfd is not a valid file descriptor, then the call fails, and newfd is not closed.

    If oldfd is a valid file descriptor, and newfd has the same value as oldfd, then dup2() does nothing, and returns newfd.

After a successful return from dup2(), the old and new file descriptor may be used interchangeably. They refer to the same open file description and thus share file offset and file status flags; for example, if the file offset is modified by using lseek() on one of the descriptors, the offset is also changed for the other.

On error, the dup2() function returns -1.
#include <unistd.h>
#include <fcntl.h>

int main(int ac, char *av[], char *env[])
{
    (void) ac;
    (void) av;
    int in;
    int out;
    char *grep_args[] = {"grep", "Lausanne", NULL};
    
    // open input and output files (assuming both files exist)
    in = open("in", O_RDONLY);
    out = open("out", O_WRONLY); 
    
    // replace standard input with input file
    dup2(in, 0);
    // close unused file descriptors
    close(in);
    close(out);
    
    // execute grep
    execve("grep", grep_args, env);
}

In this example, first we open both in and out file, in reading and writing mode respectively.

Then we use dup2() to replace the stdin file descriptor by the in file descriptor.
This way, whatever the command that comes after will read from the stdin will be whatever the content of in is since the stdin file descriptor now "points" to the in file.

Then, we can close in and out, we don't use them anymore, right ?

We set the stdin file descriptor to be the same as in, so now we only use stdin, in and out are not used anymore, we can close them.

Now, we use the execve() function to execute the grep shell command (this is explained below on this page). When grep is launched without any argument, it reads text from the standard input before executing. What will happen then ? 

Remember we replaced the stdin file descriptor by in, so grep will read from the standard input, the standard input now reads from the in file, so grep will execute on whatever the content of the in file is.
You can find more information on dup2() here: https://linux.die.net/man/2/dup2
----------------------------------------------------------------------------------

int pipe(int pipefd[2]);

pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe

On success, 0 is returned. On error, -1 is returned, and errno is set appropriately.
-------------------------------------------------------------------------------------

Example of Environment Variables:
        PATH: Defines the system paths where executables can be found.
        HOME: Specifies the home directory of the user.
        USER: The username of the current user.
---------------------------------------------------------------------------------------

int execve(const char *filename, char *const argv[], char *const envp[]);
execve() executes the program pointed to by filename.
execve() does not return on succes, the calling process is replaced by the executed filename.

After calling execve, the current process is replaced entirely by the new program, so any code after execve does not run unless execve fails.
---------------------------------------------------------------------------------------------

int unlink(const char *pathname);

unlink() deletes a name from the file system. If that name was the last link to a file and no processes have the file open the file is deleted and the space it was using is made available for reuse.

If the name was the last link to a file but any processes still have the file open the file will remain in existence until the last file descriptor referring to it is closed.

On success, 0 is returned. On error, -1 is returned, and errno is set appropriately.
------------------------------------------------------------------------------------------------

Commands like ls, grep, and cat are stored as binary files in specific directories, such as:

    /bin
    /usr/bin
    /usr/local/bin

You need to:

    Search these directories to check if the binary file for the command exists.
    Use access() from <unistd.h> to verify the file's existence and whether it is executable.
---------------------------------------------------------------------------------------------------

    int execve(const char *path, char *const argv[], char *envp[]);

int execve(const char *path, char *const argv[], char *envp[]);# path: the path to our command
        type `which ls` and `which wc` in your terminal
        you'll see the exact path to the commands' binaries# argv[]: the args the command needs, for ex. `ls -la`
          you can use your ft_split to obtain a char **
          like this { "ls", "-la", NULL }
          it must be null terminated# envp: the environmental variable
        you can simply retrieve it in your main (see below)
        and pass it onto execve, no need to do anything here
        in envp you'll see a line PATH which contains all possible
        paths to the commands' binariesint main(int ac, char **ag, char **envp)
{
     int f1;
     int f2;     f1 = open(ag[1], O_RDONLY);
     f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
     if (f1 < 0 || f2 < 0)
          return (-1);
     pipex(f1, f2, ag, envp);
     return (0);
}

To see what is inside envp, type env in your terminal.
You’ll see a line PATH , those are all the possible paths to the command binaries.
You’ll need to split: you can use : as a delimiter, and retrieve them (small note on this in section 4).
Your execve function will have to try every possible path to the cmd until it finds the good one.
To see the path to the command ls, for ex., you can type which ls in your terminal. If the command does not exist, execve will do nothing and return -1; else, it will execute the cmd, delete all ongoing processes (including variables, so no need to worry about free) and exit (more on this, see section 3 below). In pseudo code,

/ parsing (somewhere in your code)char *PATH_from_envp;
char **mypaths;
char **mycmdargs;// retrieve the line PATH from envp
PATH_from_envp = ft_substr(envp ....);
mypaths = ft_split(PATH_from_envp, ":"); // see section 4 for a
                                            small note[0]
mycmdargs = ft_split(ag[2], " ");// in your child or parent processint  i;
char *cmd;i = -1;
while (mypaths[++i])
{
    cmd = ft_join(mypaths[i], ag[2]); // protect your ft_join
    execve(cmd, mycmdargs, envp); // if execve succeeds, it exits
    // perror("Error"); <- add perror to debug
    free(cmd) // if execve fails, we free and we try a new path
}
return (EXIT_FAILURE);

We can divide the pipex workload on different children, while the parent waits for the job to be done and supervise the children’s status.

We will thus have to fork twice, and assign child1 to execute cmd1, and child2 to execute cmd2. The parent will wait at the end. In pseudo code,

void    pipex(int f1, int f2, char *cmd1, char *cmd 2)
{
    int   end[2];
    int   status;
    pid_t child1;
    pid_t child2;    pipe(end);
    child1 = fork();
    if (child1 < 0)
         return (perror("Fork: "));
    if (child1 == 0)
        child_one(f1, cmd1);
    child2 = fork();
    if (child2 < 0)
         return (perror("Fork: "));
    if (child2 == 0)
        child_two(f2, cmd2);
    close(end[0]);         // this is the parent
    close(end[1]);         // doing nothing
    waitpid(child1, &status, 0);  // supervising the children
    waitpid(child2, &status, 0);  // while they finish their tasks
}
----------------------------------------------------------------------------------

3 — The access() function

If you run < infile pikachu | ls > oufile in the shell, you’ll get -bash: pikachu: command not found.
If you now run ./pipex infile pikachu ls outfile, your program will do nothing and exit without error messages. execve() will execute nothing if the command is not found. You need to check if it exists before its execution.
To do this, check the access() function. With the proper mode, you can use it to verify whether the command exists and is executable.
------------------------------------------------------------------------------------

4 — Frequently encountered problems

[0] As for splitting your envp path, print out the result of your split and have a look. Add a / at the end for the path to work correctly.

[1] If you launch your program and it gets stuck without executing anything, most probably one end of the pipe has not been closed correctly. Until one end is open, the other will be waiting for input and its process will not finish.

[2] Use perror("Error") to debug, especially right after fork() or execve(), to see what is going on in the pipe. Inside the pipe, everything done goes to one of its ends. printf for ex. won’t print to the terminal or it will print to your outfile (because we swapped the stdout); perror("Error") will work because it prints to stderr.

[3] Handle file rights when you open() them. Return error if the file cannot be opened, read or written. Check how the shell treats infile and outfile when they do not exist, are not readable, writable etc. (chmod is your best friend).

