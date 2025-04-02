

#include "../../includes/minishell.h"

int	env_builtin(char **env)
{
	size_t	i;

	i = 0;
	if (!env)
		return (EXIT_SUCCESS);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i] || !env[i][5])
	{
		write(STDERR_FILENO, "minishell: env: No such file or directory\n", 42);
		return (127);
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
