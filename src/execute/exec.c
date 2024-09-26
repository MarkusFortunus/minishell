/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimard <msimard@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:21:54 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/26 15:57:27 by msimard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_clearup(char *arg, char **tab, char *error, int exit)
{
	ft_error(arg, NULL, error, exit);
	ft_free(tab, NULL);
}

static void	ft_exec(t_data *data, t_pipe_cmd *node, char *cmd_path, int i)
{
	char	**envp;
	char	**cmd_arg;

	cmd_arg = ft_get_envp_cpy(node->cmd_arg);
	envp = ft_get_envp_cpy(data->envp);
	if (ft_is_directory(cmd_path))
	{
		ft_clearup(cmd_arg[i], envp, ": is a directory\n", 126);
		ft_free(cmd_arg, NULL);
		if (cmd_path)
			free(cmd_path);
		exit(126);
	}
	if (execve(cmd_path, cmd_arg, envp) == -1)
	{
		ft_clearup(cmd_arg[i], envp, ": command not found\n", 127);
		ft_free(cmd_arg, NULL);
		if (cmd_path)
			free(cmd_path);
		exit(127);
	}
	ft_free(envp, NULL);
	ft_free(cmd_arg, NULL);
	if (cmd_path)
		free(cmd_path);
}

bool	ft_check_cmd_errors(t_data *data, t_pipe_cmd *node, char *cmd_path)
{
	if (!cmd_path && errno == EISDIR)
	{
		ft_error(node->cmd_arg[node->x], NULL, ": is a directory\n", 126);
		close(data->fd[1]);
		ft_exit_cmd(data, node, false);
		exit(126);
	}
	if (!cmd_path)
	{
		ft_error(node->cmd_arg[node->x], NULL, ": command not found\n", 127);
		free(cmd_path);
		close(data->fd[1]);
		ft_exit_cmd(data, node, false);
		exit(127);
	}
	return (true);
}

void	ft_execute(t_data *data, t_pipe_cmd *node)
{
	char	*cmd_path;
	int		i;

	free(data->pidt);
	if (!node->cmd_arg[node->x] || ft_strlen(node->cmd_arg[node->x]) == 0)
	{
		g_exit_stat = 0;
		close(data->fd[1]);
		ft_exit_cmd(data, node, true);
	}
	i = node->x;
	cmd_path = ft_search_path(node->cmd_arg[node->x], data->envp);
	ft_check_cmd_errors(data, node, cmd_path);
	ft_exec(data, node, cmd_path, i);
}
