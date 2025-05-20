/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   funcs_practise.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 18:09:56 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/05/20 18:17:02 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>


/**
 * cc -Wall -Werror -Wall -pthread mutex.c && ./a.out
   for i in {1..40}; do ./a.out; done
 */
int main()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("-- %ld --\n", time_ms);
	return (0);
}