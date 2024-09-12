/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onault <onault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:20:53 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 16:08:12 by onault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_index_cmd_arg(t_pipe_cmd *node)
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

int	ft_do_cmd(t_pipe_cmd *node, t_data *data)
{
	if (stdout_file(node) || stdin_file(node, data))
		return (g_exit_stat);
	if (node->cmd_arg && node->cmd_arg[node->x])
	{
		if (!ft_strncmp(node->cmd_arg[node->x], "env", 4))
			ft_env_cmd(node->env);
		else if (!ft_strncmp(node->cmd_arg[node->x], "export", 7))
			return (ft_export_cmd(node, data));
		else if (!ft_strncmp(node->cmd_arg[node->x], "cd", 3))
			return (ft_chdir(node->cmd_arg[node->x + 1], node, data));
		else if (!ft_strncmp(node->cmd_arg[node->x], "exit", 5))
			return (ft_exit_cmd(data, node, true));
		else if (!ft_strncmp(node->cmd_arg[node->x], "pwd", 4))
			ft_pwd_cmd();
		else if (!ft_strncmp(node->cmd_arg[node->x], "unset", 6))
			ft_unset(node, data);
		else if (!ft_strncmp(node->cmd_arg[node->x], "echo", 5))
			return (ft_echo(node));
	}
	return (EXIT_SUCCESS);
}

bool	is_builtin(t_pipe_cmd *node)
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
