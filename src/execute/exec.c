/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:21:54 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 15:41:36 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec(t_data *data, t_pipe_cmd *node, char *cmd_path, int i)
{
	char	**envp;
	char	**cmd_arg;

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

void	ft_execute(t_data *data, t_pipe_cmd *node)
{
	char	*cmd_path;
	int		i;

	if (ft_strlen(node->cmd_arg[node->x]) == 0)
	{
		g_exit_stat = 0;
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
	ft_exec(data, node, cmd_path, i);
}
