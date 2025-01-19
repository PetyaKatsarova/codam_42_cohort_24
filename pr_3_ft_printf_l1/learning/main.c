/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 12:50:21 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/10/19 12:55:35 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * Variadic functions are functions that accept a variable number of arguments, like printf() in the standard C library. To manage these arguments, the stdarg.h library provides macros: va_start, va_arg, va_copy, and va_end.
To use these macros, you need to include the header: #include <stdarg.h>
 * 
*/
#include <stdio.h>
#include <stdarg.h>

int sum(int num_args, ...) {
    va_list args; // declare
    va_start(args, num_args); // populate
    int total = 0;

    for (int i=0; i<num_args; i++)
        total += va_arg(args, int); // get next el of type int
    va_end(args); // clean up
    return total;
}

void print_args(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    for (const char *p = format;  *p != '\0'; p++) {
        if (*p == 'd') {
            int i = va_arg(args, int);
            printf("%d --", i);
        } else if (*p == 'c') {
            char c = (char) va_arg(args, int);
            printf("%c --", c);
        } else if (*p == 'f') {
            double d = va_arg(args, double);
            printf("%f --", d);
        }
    }
    va_end(args);
    printf("\n");
}

int main() {
    int res1 = sum(3, 1,2,3); //6
    int res2 = sum(5, 10,20,30,40,50); //150

    printf("Res 1: %d\n", res1);
    printf("Res 2: %d\n", res2);
    print_args("dcf", 10, 'A', 3.14);
    print_args("ddd", 1,2,3);
    print_args("cfd", 'b', 2.42, 42);
}

