#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * man 2 dup2
 * perror = print a sys err msg
 * man -k printf
 * 
 *  pipe(pipe_fd)
    Creates a pipe, which is a unidirectional communication channel.
    pipe_fd[0]: Read end of the pipe.
    pipe_fd[1]: Write end of the pipe.

    fork()

    Creates a child process by duplicating the current process.
    Returns:
        0 in the child process.
        Child's process ID in the parent process.
        -1 if the fork fails.

    open()
    Opens a file and returns a file descriptor.
    Example:
        O_RDONLY: Open file for reading.
        O_WRONLY | O_CREAT | O_TRUNC: Open for writing, create if it doesn’t exist, and truncate if it does.

    dup2(old_fd, new_fd)
    Redirects new_fd to point to the same file as old_fd.
    Used for I/O redirection:
        dup2(input_fd, STDIN_FILENO): Redirects standard input (stdin) to input_fd.
        dup2(pipe_fd[1], STDOUT_FILENO): Redirects standard output (stdout) to the write end of the pipe.

    execlp()
    Replaces the current process with a new program.
    Parameters:
        "tr": Name of the program to execute.
        "tr", "a-z", "A-Z", NULL: Command-line arguments to the program.
    If it fails, it calls perror() and exits.      
*/
int main()
{
    int     pipe_fd[2];
    pid_t   pid;

    //create a pipe
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    
    // for the first child
    if ((pid = fork()) == 0)
    {
        int input_fd = open("input.txt", O_RDONLY);
        if (input_fd < 0)
        {
            perror("open input.txt");
            exit(1);
        }
        dup2(input_fd, STDIN_FILENO); // REDIRECT old fd to newfd
        dup2(pipe_fd[1], STDOUT_FILENO); // REDIRECTS the pipe first end to stdout
        close(pipe_fd[0]); // close unused read end
        execlp("tr", "tr", "a-z", "A-Z");
        perror("execlp");
        exit(1);
    }

    // fork the second child
    if ((pid = fork()) == 0)
    {
        int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd < 0)
        {
            perror("open output.txt");
            exit(1);
        }
        dup2(pipe_fd[0], STDIN_FILENO); // redirect stdin to pipe
        dup2(output_fd, STDOUT_FILENO);
        close(pipe_fd[1]); // close unused write end
        execlp("wc", "wc", "-w", NULL);
        perror("execlp");
        exit(1);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    wait(NULL); // WAIT FOR both children to finish
    wait(NULL);

    return (0);
}