/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:13 by fcornill          #+#    #+#             */
/*   Updated: 2024/10/01 11:28:02 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_ev(void)
{
	int	i;

	i = 3;
	while (i <= 200)
	{
		close(i);
		i++;
	}
}

static void	ft_doc_ctrl(char *eof, int *fd)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, ft_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
		line = get_next_line(0);
		if ((!ft_strncmp(line, eof, ft_strlen(eof))
				&& ft_strlen(eof) == (ft_strlen(line) - 1)) || line == NULL)
		{
			free(line);
			break ;
		}
		else
		{
			write(*fd, line, (ft_strlen(line)));
			free(line);
		}
	}
	close(*fd);
	close_ev();
}

bool	ft_heredoc(char *eof, t_pipe_cmd *data, t_data *ddata)
{
	t_heredoc	hrd;

	ft_bzero(&hrd, sizeof(t_heredoc));
	hrd.filename = ".EOF0";
	hrd.id = fork();
	if (hrd.id == 0)
	{
		hrd.fd = open(hrd.filename, O_WRONLY | O_CREAT | O_APPEND, 0600);
		if (hrd.fd == -1)
			return (false);
		ft_doc_ctrl(eof, &hrd.fd);
		free(ddata->pidt);
		ft_exit_cmd(ddata, data, true);
	}
	else
		waitpid(hrd.id, &hrd.status, 0);
	if (hrd.status)
		return (false);
	data->fd = open(hrd.filename, O_RDONLY);
	return (true);
}

void	ft_delete_hrd_file(void)
{
	char	*tmp_file;
	int		i;
	char	*itoa;

	i = 0;
	while (1)
	{
		itoa = ft_itoa(i);
		tmp_file = ft_strjoin(".EOF", itoa);
		free(itoa);
		if (access(tmp_file, F_OK) != 0)
		{
			free(tmp_file);
			break ;
		}
		unlink(tmp_file);
		free(tmp_file);
		i++;
	}
}
