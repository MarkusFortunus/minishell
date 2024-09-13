/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inoutfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:45 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/13 14:05:05 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_in(char *stdfile)
{
	int	file;

	file = open(stdfile, O_RDONLY);
	if ((file == -1 && errno == ENOENT && ft_error(stdfile, NULL,
				": No such file or directory\n", 1)) || (file == -1
			&& errno == EACCES && ft_error(stdfile, NULL,
				": Permission denied\n", 1)) || (dup2(file, STDIN_FILENO) == -1
			&& ft_error(NULL, NULL, "problem pipe\n", 1)))
		return (g_exit_stat);
	close(file);
	return (-1);
}

static int	open_out(char *stdfile, bool istrunc)
{
	int	file;

	file = 0;
	if (istrunc == true)
		file = open(stdfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file = open(stdfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((file == -1 && errno == ENOENT && ft_error(stdfile, NULL,
				": No such file or directory\n", 1)) || (file == -1
			&& errno == EACCES && ft_error(stdfile, NULL,
				": Permission denied\n", 1)) || (dup2(file, STDOUT_FILENO) == -1
			&& ft_error(NULL, NULL, "problem redirecting pipes\n", 1)
			&& close(file)))
		return (g_exit_stat);
	close(file);
	return (-1);
}

int	stdin_file(t_pipe_cmd *p_data, t_data *data)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (p_data->stdin_file[i])
	{
		if (p_data->heredoc[i] == true)
		{
			flag = 1;
			if (!ft_heredoc(p_data->stdin_file[i], p_data, data))
				return (EXIT_FAILURE);
		}
		else if (open_in(p_data->stdin_file[i]) == g_exit_stat)
			return (g_exit_stat);
		i++;
	}
	if (flag)
	{
		dup2(p_data->fd, 0);
		close(p_data->fd);
	}
	return (EXIT_SUCCESS);
}

int	stdout_file(t_pipe_cmd *p_data)
{
	int	i;

	i = 0;
	while (p_data->stdout_file[i])
	{
		if (open_out(p_data->stdout_file[i], p_data->trunc[i]) == g_exit_stat)
			return (g_exit_stat);
		i++;
	}
	return (EXIT_SUCCESS);
}
