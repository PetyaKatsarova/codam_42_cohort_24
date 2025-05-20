#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 *   gcc -o exec_command exec_command.c
    ./exec_command grep a input.txt
*/

// Function to check if a command exists in standard directories
const char *find_binary(const char *command) {
    const char *paths[] = {"/bin", "/usr/bin", "/usr/local/bin", NULL};
    static char full_path[256];

    for (int i = 0; paths[i] != NULL; i++) {
        snprintf(full_path, sizeof(full_path), "%s/%s", paths[i], command);

        // Check if the binary exists and is executable
        if (access(full_path, X_OK) == 0) {
            return full_path;
        }
    }

    return NULL; // Not found
}

int main(int argc, char *argv[], char *envp[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return 1;
    }

    // Find the binary for the given command
    const char *binary_path = find_binary(argv[1]);
    if (!binary_path) {
        fprintf(stderr, "Command not found: %s\n", argv[1]);
        return 1;
    }

    // Build the arguments array for execve
    char *exec_args[argc];
    for (int i = 0; i < argc - 1; i++) {
        exec_args[i] = argv[i + 1];
    }
    exec_args[argc - 1] = NULL; // Null-terminate the array

    // Execute the command
    execve(binary_path, exec_args, envp);

    // If execve fails, print the error
    perror("execve failed");
    return 1;
}
