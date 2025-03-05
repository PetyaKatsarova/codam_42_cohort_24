#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	char			*tag;
	struct s_list	*next;
}	t_list;

t_list	*init_node(char *word)
{
	t_list *new = malloc(sizeof(t_list));
	new->tag = word;
	new->next = NULL;
	return (new);
}

t_list *last_node(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_add_back(t_list **lst, t_list *new)
{
	t_list *back;
	if (*lst)
	{
		back = last_node(*lst);
		back->next = new;
	}
	else
		*lst = new;
}

char	*extract_tag(char *str, int len)
{
	int i = 0;
	char *tag = malloc(sizeof(char) * (len + 1));
	while (i < len && str[i] != ' ' && str[i] != '/')
	{
		tag[i] = str[i];
		i++;
	}
	tag[i] = '\0';
	return (tag);
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_match(t_list **lst, char *word, int len)
{
	if (*lst == NULL)
		return (1);
	t_list *current = *lst;
	t_list *previous = NULL;

	while (current && current->next)
	{
		previous = current;
		current = current->next;
	}
	if (len == ft_strlen(current->tag))
	{
		if (current && strncmp(current->tag, word, len) == 0)
		{
			if (previous == NULL)
				*lst = NULL;
			else
				previous->next = NULL;
			free(current->tag);
			free(current);
			return (0);
		}
	}
	else
		return (1);
}

int	validator(char *str)
{
	int i = 0;
	t_list *stack = NULL;

	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '/')
		{
			int start = i + 1;
			while (str[i] != '>')
				i++;
			if (str[i] == '>')
			{
				int len = i - start;
				char *word = extract_tag(&str[start], len);
				if (strncmp(word, "img", 3) == 0)
					i = start;
				else
				{
					t_list *new = init_node(word);
					lst_add_back(&stack, new);
				}
			}
			i = start;
		}
		if (str[i] == '<' && str[i + 1] == '/')
		{
			int start = i + 2;
			while (str[i] != '>')
				i++;
			if (str[i] == '>')
			{
				int len = i - start;
				char *word = extract_tag(&str[start], len);
				if (check_match(&stack, word, len) == 1)
				{
					t_list *temp;
					while (stack)
					{
						temp = stack;
						stack = stack->next;
						free(temp->tag);
						free(temp);
					}
					return (1);
				}
			}
			i = start;
		}
		i++;
	}
	if (stack != NULL)
	{
		t_list *temp;
		while (stack)
		{
			temp = stack;
			stack = stack->next;
			free(temp->tag);
			free(temp);
		}
		return (1);
	}
	else
		return (0);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (validator(argv[1]) == 0)
			return (0);
		else
			return (1);
	}
	return (1);
}