/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:48:32 by msimard           #+#    #+#             */
/*   Updated: 2024/09/11 17:45:55 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_dup(t_data *data, int i)
{
	if (i != 0)
	{
		dup2(data->prev, STDIN_FILENO);
		close(data->prev);
	}
	if (i < data->arg_count - 1)
	{
		close(data->fd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
	}
	else
		close(data->fd[0]);
}

static void	pipe_cmd(t_pipe_cmd *p_data, t_data *data, int i)
{
	close_dup(data, i);
	if (stdout_file(p_data) || stdin_file(p_data))
		// ft_printf("%d\n", g_exit_stat);
		exit(g_exit_stat);
	if (is_builtin(p_data))
	{
		g_exit_stat = ft_do_cmd(p_data, data);
		close(data->fd[1]);
		free(data->pidt);
		ft_exit_cmd(data, p_data, true);
	}
	else if (p_data->cmd_arg && p_data->cmd_arg[p_data->x])
		ft_execute(data, p_data);
	exit(EXIT_SUCCESS);
}

static int	pipe_fork(t_data *data, int i, t_pipe_cmd *p_data)
{
	int	pid;

	if (pipe(data->fd) == -1)
	{
		perror("pipe");
		return (false);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (false);
	}
	signal(SIGINT, ft_child_handler);
	signal(SIGQUIT, ft_child_handler);
	if (!pid)
		pipe_cmd(p_data, data, i);
	return (pid);
}

static void	forkwait(t_data *data, int i, int *pid)
{
	int	status;

	status = 0;
	while (--i >= 0)
	{
		if (waitpid(pid[i], &status, 0) != -1 && i == data->arg_count - 1)
			g_exit_stat = ft_err_code(status);
		else if ((i != data->arg_count - 1) && WIFSIGNALED(status)
			&& (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT))
			g_exit_stat = (128 + WTERMSIG(status));
	}
}

bool	each_pipe(t_pipe_cmd *p_data, t_data *data)
{
	int	i;
	int	*pid;

	pid = malloc(data->arg_count * (sizeof(int)));
	data->pidt = pid;
	i = 0;
	while (p_data)
	{
		data->pidt[i] = pipe_fork(data, i, p_data);
		if (i != 0)
			close(data->prev);
		if (i < data->arg_count)
		{
			close(data->fd[1]);
			data->prev = data->fd[0];
		}
		i++;
		p_data = p_data->next;
	}
	close(data->fd[0]);
	forkwait(data, i, data->pidt);
	free(data->pidt);
	return (true);
}
