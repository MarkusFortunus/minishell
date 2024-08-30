#include "minishell.h"

int	ft_execute(char **envp, pipe_cmd_t *node)
{
	char	*cmd_path;

	cmd_path = ft_search_path(node->cmd_arg[node->x], envp);
	if (!cmd_path)
	{
		ft_error(node->cmd_arg[node->x], NULL, ": command not found\n", 127);
		ft_free_lst(node);
		rl_clear_history();
		exit(127);
	}
	else
	{
		if (execve(cmd_path, node->cmd_arg, envp) == -1)
			return (ft_error(NULL, NULL, "Wrong command\n", 1));
		ft_error(node->cmd_arg[node->x], NULL, ": command not found\n", 127);
		ft_free_lst(node);
	}
	return (0);
}
