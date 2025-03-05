/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/12 11:42:55 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/11/09 15:55:30 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// all from root:
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=2 main.c with_dbl_ptr/get_next_line.c with_dbl_ptr/get_next_line_utils.c
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000000 main.c with_dbl_ptr/get_next_line.c with_dbl_ptr/get_next_line_utils.c
//cc -Wall -Wextra -Werror -D BUFFER_SIZE=0 main.c with_dbl_ptr/get_next_line.c with_dbl_ptr/get_next_line_utils.c
// valgrind cc -Wall -Wextra -Werror -D BUFFER_SIZE=2 main.c with_dbl_ptr/get_next_line.c with_dbl_ptr/get_next_line_utils.c

void print_with_diff_fd(int fd, char *file_name);

int main() {
    // int stdin1 = 0;
    int fd1 = open("ex.txt", O_RDONLY);
    int fd2 = open("ex2.txt", O_RDONLY);
    int fd3 = open("ex3.txt", O_RDONLY);

    if (fd1 == -1 || fd2 == -1 || fd3 == -1) {
        perror("Error opening files");
        return 1;
    }

    // // print_with_diff_fd(fd, "test");
    print_with_diff_fd(fd1, "ex.txt");
    print_with_diff_fd(fd2, "ex2.txt");
    print_with_diff_fd(fd1, "ex.txt");
    print_with_diff_fd(fd3, "ex3.txt");
    print_with_diff_fd(fd1, "ex.txt");
    print_with_diff_fd(fd1, "ex.txt");
    print_with_diff_fd(fd2, "ex2.txt");
    print_with_diff_fd(fd1, "ex.txt");
    print_with_diff_fd(fd3, "ex3.txt");
    print_with_diff_fd(fd1, "ex.txt");

    // Close all files
    // close(fd1);
    // close(fd2);
    // close(fd3);

    return 0;
}

void print_with_diff_fd(int fd, char *file_name) {
    char *l = get_next_line(fd);
    if (l != NULL) {
        printf("-- line from %s (fd: %d): %s", file_name, fd, l);
        free(l);
    } else {
        printf("No more lines in %s (fd: %d)\n", file_name, fd);
    }
}