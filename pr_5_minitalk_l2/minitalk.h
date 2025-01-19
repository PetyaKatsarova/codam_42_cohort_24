
#ifndef MINITALK_H
# define MINITALK_H

#define _POSIX_C_SOURCE 200809L
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <locale.h>

void	ft_putnbr(int n);
void	ft_putchar(char c);
int		ft_atoi(char *str);

#endif