/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimard <msimard@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:13:43 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 20:17:49 by msimard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exit_with_arg(t_data *data, t_pipe_cmd *node)
{
	int	exit_val;
	int	x;

	x = 0;
	while (node->cmd_arg[1][x])
	{
		if (!ft_isdigit(node->cmd_arg[1][x]) && node->cmd_arg[1][x] != '+'
			&& node->cmd_arg[1][x] != '-')
		{
			ft_error("exit: ", NULL, "numeric argument required\n", 255);
			ft_free_exit(data, node);
			exit(255);
		}
		x++;
	}
	exit_val = ft_atoi(node->cmd_arg[1]);
	return (exit_val);
}

static void exit_only_cmd(t_pipe_cmd *node, t_data *data)
{
	if (data->arg_count == 1)
	{
		close(node->stdout);
		close(node->stdin);
	}
}

int	ft_exit_cmd(t_data *data, t_pipe_cmd *node, bool need_exit)
{
	int	exit_val;

	exit_only_cmd(node, data);
	exit_val = 0;
	if (node->arg_cnt > 1 && node->cmd_arg[1] && !ft_strncmp(node->cmd_arg[node->x], "exit", 5))
	{
		if (node->cmd_arg[2])
			return (ft_error("exit: ", NULL, "too many arguments\n", 1));
		exit_val = ft_exit_with_arg(data, node);
	}
	if (exit_val > 255)
	{
		g_exit_stat = exit_val - 256;
		if (g_exit_stat > 255)
			g_exit_stat = 255;
	}
	else
		g_exit_stat = exit_val;
	ft_free(data->args, NULL);
	ft_free_exit(data, node);
	if (need_exit)
		exit(g_exit_stat);
	return (0);
}
