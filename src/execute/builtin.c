#include "minishell.h"

int	ft_do_cmd(pipe_cmd_t *node, t_data *data)
{
	if (stdout_file(node) || stdin_file(node))
		return (exit_status);
	if (node->cmd_arg && node->cmd_arg[0]) // pour en finir une fois pour toute avec env :P
	{
		if (!ft_strncmp(node->cmd_arg[0], "env", 4))
			ft_env_cmd(node->env);
		else if (!ft_strncmp(node->cmd_arg[0], "export", 7))
			return (ft_export_cmd(node, data));
		else if (!ft_strncmp(node->cmd_arg[0], "cd", 3))
			return (ft_chdir(node->cmd_arg[1], node, data));
		else if (!ft_strncmp(node->cmd_arg[0], "exit", 5))
			return (ft_exit_cmd(data, node, true));
		else if (!ft_strncmp(node->cmd_arg[0], "pwd", 4))
			ft_pwd_cmd();
		else if (!ft_strncmp(node->cmd_arg[0], "unset", 6))
			ft_unset(node, data);
		else if (!ft_strncmp(node->cmd_arg[0], "echo", 5))
			return (ft_echo(node));
	}
	if (node->stdfd != STDIN_FILENO)
		dup2(node->stdfd, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

bool	is_builtin(pipe_cmd_t *node)
{
	if (node->cmd_arg && node->cmd_arg[0])
	{
		if (!ft_strncmp(node->cmd_arg[0], "env", 4))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[0], "export", 7))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[0], "cd", 3))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[0], "exit", 5))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[0], "pwd", 4))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[0], "unset", 6))
			return (true);
		else if (!ft_strncmp(node->cmd_arg[0], "echo", 5))
			return (true);
	}
	return (false);
}
