
#include "../../includes/minishell.h"

int	pwd_builtin(void)
{
	char	buffer[PATH_MAX + 1];

	if (!getcwd(buffer, PATH_MAX + 1))
	{
		perror("minishell: pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", buffer);
	return (EXIT_SUCCESS);
}
