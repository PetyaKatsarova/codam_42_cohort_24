/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:05:59 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 16:33:11 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

/* Struct Definitions */
typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}	t_stack;

/* Function Prototypes */

/* cost.c */
void			get_cost(t_stack **stack_a, t_stack **stack_b);
void			do_cheapest_move(t_stack **stack_a, t_stack **stack_b);

/* init.c */
t_stack			*populate_list(int argc, char **argv);
void			assign_index(t_stack *stack_a, int ac);

/* input_check_utils.c & input_check.c */
int				is_digit(char c);
int				is_sign(char c);
int				nbstr_cmp(const char *s1, const char *s2);
int				count_words(char **str);
char			**split_argv(const char *input);
int				is_correct_input(char **argv);

/* list.c */
t_stack			*create_node(int val);
int				list_size(t_stack *stack);
t_stack			*get_last(t_stack *list);
t_stack			*get_second_last(t_stack *list);
void			add_last(t_stack **list, t_stack *node);

/* main.c */
int				is_sorted(t_stack *list);
int				main(int argc, char **argv);

/* move.c */
void			move(t_stack **a, t_stack **b, int cost_a, int cost_b);

/* positions.c */
int				get_pos_lowest_index(t_stack **list);
void			set_target_pos(t_stack **a, t_stack **b);

/* push.c */
void			pa(t_stack **list_a, t_stack **list_b);
void			pb(t_stack **list_a, t_stack **list_b);

/* swap.c */
void			sa(t_stack **list);
void			sb(t_stack **list);
void			ss(t_stack **list_a, t_stack **list_b);

/* rotate.c */
void			ra(t_stack **a);
void			rb(t_stack **a);
void			rr(t_stack **a, t_stack **b);

/* reverse_rotate.c */
void			rrr(t_stack **stack_a, t_stack **stack_b);
void			rra(t_stack **stack_a);
void			rrb(t_stack **stack_b);

/* tiny_sort.c & sort.c */
void			tiny_sort(t_stack **stack);
void			sort(t_stack **stack_a, t_stack **stack_b);

/* utils.c */
void			free_list(t_stack **list);
void			exit_error(t_stack **stack_a, t_stack **stack_b);
long int		ft_atoi(const char *str);
void			ft_putstr(char *str);
char			*ft_strchr(const char *s, int c);
int				abs_val(int num);

/* ft_split.c, ft_strlen.c, free_argv.c */
char			**ft_split(char const *s, char c);
unsigned int	ft_strlen(const char *str);
void			free_argv(char **argv);
void			is_all_correct(int argc, char **argv);

#endif
