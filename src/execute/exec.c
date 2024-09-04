#include "minishell.h"

void	ft_execute(t_data *data, pipe_cmd_t *node)
{
	char	*cmd_path;
	char **cmd_arg;
	char **envp;
	int 	i;

	if (ft_strlen(node->cmd_arg[node->x]) == 0)
	{
		exit_stat = 0;
		close(data->fd[1]);
		ft_exit_cmd(data, node, true);
	}
	i = node->x;
	cmd_path = ft_search_path(node->cmd_arg[node->x], data->envp);
	rl_clear_history();
	if (!cmd_path)
	{
		ft_error(node->cmd_arg[node->x], NULL, ": command not found\n", 127);
		free(cmd_path);
		close(data->fd[1]);
		ft_exit_cmd(data, node, false);
		exit(127);
	}
	cmd_arg = ft_get_envp_cpy(node->cmd_arg);
	envp = ft_get_envp_cpy(data->envp);
	ft_exit_cmd(data, node, false);
	execve(cmd_path, cmd_arg, envp);
	ft_error(cmd_arg[i], NULL, ": command not found\n", 127);
	ft_free(envp, NULL);
	ft_free(cmd_arg, NULL);
	free(cmd_path);
	exit(127);
}
