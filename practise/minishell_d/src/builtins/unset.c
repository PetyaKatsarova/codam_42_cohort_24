
#include "../../includes/minishell.h"

int	unset_builtin(t_cmd *cmd, t_data *data)
{
	size_t	i;

	i = 1;
	while (cmd->args[i])
	{
		if (data)
			data->env = delete_env_var(cmd->args[i], data->env);
		else
			cmd->env = delete_env_var(cmd->args[i], cmd->env);
		i++;
	}
	return (EXIT_SUCCESS);
}
