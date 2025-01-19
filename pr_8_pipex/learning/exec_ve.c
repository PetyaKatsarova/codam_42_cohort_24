#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int ac, char **av, char **envp)
{
    (void) ac;
    (void) av;

    // Open input.txt for reading
    int input_fd = open("input.txt", O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open input.txt");
        return 1;
    }

    // Open output.txt for writing (create it if it doesn't exist)
    int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        perror("Failed to open output.txt");
        close(input_fd); // Clean up
        return 1;
    }

    // Redirect stdin to input.txt
    if (dup2(input_fd, STDIN_FILENO) < 0) {
        perror("Failed to redirect stdin");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    // Redirect stdout to output.txt
    if (dup2(output_fd, STDOUT_FILENO) < 0) {
        perror("Failed to redirect stdout");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    // Close the original file descriptors as they are no longer needed
    close(input_fd);
    close(output_fd);

    // Execute the grep command
    /**
     * NB!!
    The path /usr/bin/grep is the absolute path to the grep program, which is a standard Unix/Linux command-line utility used to search for text patterns in files or input.
    */
    const char *filename = "/usr/bin/grep";
    char *const argv[] = {"/usr/bin/grep", "a", NULL}; // search for lines containing 'a'

    execve(filename, argv, envp);

    // If execve fails, print an error and exit
    perror("execve failed");
    return 1;
}
