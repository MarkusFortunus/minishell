/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onault <onault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:15:28 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 17:07:12 by onault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst(t_pipe_cmd *node)
{
	t_pipe_cmd	*tmp;

	while (node)
	{
		tmp = node;
		node = node->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->stdin_file)
			ft_free(tmp->stdin_file, NULL);
		if (tmp->env)
			ft_free(tmp->env, NULL);
		if (tmp->stdout_file)
			ft_free(tmp->stdout_file, NULL);
		if (tmp->cmd_arg)
			ft_free(tmp->cmd_arg, NULL);
		if (tmp->trunc)
			free(tmp->trunc);
		if (tmp->heredoc)
			free(tmp->heredoc);
		free(tmp);
	}
}

void	ft_free(char **to_free, char *exit)
{
	int	i;

	if (!to_free)
		return ;
	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	to_free = NULL;
	if (exit)
		ft_error(NULL, NULL, exit, 1);
}

void	ft_free_data(t_data *data)
{
	free(data->prompt);
	free(data->pidt);
	if (data->envp)
		ft_free(data->envp, NULL);
	free(data);
}

void	ft_free_exit(t_data *data, t_pipe_cmd *node)
{
	if (node->pos > 0)
	{
		ft_free_lst(node->start_ls);
	}
	else
		ft_free_lst(node);
	free(data->input);
	ft_free_data(data);
}
