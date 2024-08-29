#include "minishell.h"

int	ft_get_index_cmd_arg(pipe_cmd_t *node)
{
	int	x;

	x = 0;
	while (node->cmd_arg[x])
	{
		if (node->cmd_arg[x][0] == '\0')
			x++;
		else
			return (x);
	}
	return (0);
}

int	ft_do_cmd(pipe_cmd_t *node, t_data *data)
{
	if (stdout_file(node) || stdin_file(node))
		return (exit_status);
	if (node->cmd_arg && node->cmd_arg[node->x]) // pour en finir une fois pour toute avec env :P
	{
		if (!ft_strncmp(node->cmd_arg[node->x], "env", 4))
			ft_env_cmd(node->env);
		else if (!ft_strncmp(node->cmd_arg[node->x], "export", 7))
			return (ft_export_cmd(node, data));
		else if (!ft_strncmp(node->cmd_arg[node->x], "cd", 3))
			return (ft_chdir(node->cmd_arg[node->x  + 1], node, data));
		else if (!ft_strncmp(node->cmd_arg[node->x], "exit", 5))
			return (ft_exit_cmd(data, node, true));
		else if (!ft_strncmp(node->cmd_arg[node->x], "pwd", 4))
			ft_pwd_cmd();
		else if (!ft_strncmp(node->cmd_arg[node->x], "unset", 6))
			ft_unset(node, data);
		else if (!ft_strncmp(node->cmd_arg[node->x], "echo", 5))
			return (ft_echo(node));
	}
	if (node->stdfd != STDIN_FILENO)
		dup2(node->stdfd, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

bool	is_builtin(pipe_cmd_t *node)
{

	node->x = ft_get_index_cmd_arg(node);
	if (node->cmd_arg && node->cmd_arg[node->x])
	{
		if (!ft_strncmp(node->cmd_arg[node->x], "env", 4))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[node->x], "export", 7))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[node->x], "cd", 3))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[node->x], "exit", 5))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[node->x], "pwd", 4))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[node->x], "unset", 6))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[node->x], "echo", 5))
			return (true);
	}
	return (false);
}
