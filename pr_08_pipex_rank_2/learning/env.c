#include <stdio.h>
#include <string.h>

int main(int ac, char *av[], char *env[]) {
    // Print all environment variables
    for (int i = 0; env[i] != NULL; i++) {
        printf("[%d] %s\n", i, env[i]);
    }

    // Accessing a specific environment variable using envp
    for (int i = 0; env[i] != NULL; i++) {
        if (strstr(env[i], "PATH=") == env[i]) { // Check if it starts with "PATH="
            printf("\nFound PATH: %s\n", env[i]);
            break;
        }
    }

    return 0;
}