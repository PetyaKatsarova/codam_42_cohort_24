
#include "../../includes/minishell.h"

int	export_print_env(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**export_error_msg(char *arg)
{
	write(STDERR_FILENO, "minishell: export: `", 20);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	return (NULL);
}
