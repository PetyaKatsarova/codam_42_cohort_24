/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/29 11:50:03 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/07 11:14:11 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "includes/push_swap.h"

/**
• In case of error, it must display "Error" followed by a ’\n’ on the standard error.
Errors include for example: some arguments aren’t integers, are bigger than an integer and/or there are duplicates.
 * 
*/

/** to_num:
 * if !int or bigger/smaller than max/min int: exit with std err
*/
static int to_num(char *str) {
    int     i = 0;
    long    result = 0;
    int     sign = 1;

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+')
        i++;
    
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            exit_error(NULL, NULL);
        result = result * 10 + (str[i] - '0');
        if (result * sign > INT_MAX || result * sign < INT_MIN)
            exit_error(NULL, NULL);
        i++;
    }
    return (int) (result * sign);
}

static int is_duplicate(char **argv) {
   int  i;
   int  j;

   i = 1;
   while (argv[i])
   {
        j = 1;
        while (argv[j])
        {
            if (j != i && ft_strncmp(argv[i], argv[j], INT_MAX) == 0)
                exit_error(NULL, NULL);
        }
   }
    return (0);
}

int validate(int argc, char **argv) {
    if (argc < 2)
        return 0;

    for (int i = 1; i < argc; i++)
        to_num(argv[i]); // exits with err if not num
    is_duplicate(argv); // or are duplicates
    return (1);
}
