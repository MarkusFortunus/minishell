/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimard <msimard@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:27:13 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 15:49:26 by msimard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_doc_ctrl(t_heredoc *doc, char *eof, int *fd)
{
	char	*line;

	(void)doc;
	while (1)
	{
		signal(SIGINT, ft_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
		line = get_next_line(0);
		if (!ft_strncmp(line, eof, ft_strlen(eof))
			&& ft_strlen(eof) == (ft_strlen(line) - 1))
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
	//close(*fd);
	//*fd = open(doc->filename, O_RDONLY);
	//if (dup2(*fd, 0) == -1)
	//	printf("dup2 error\n");
	close(*fd);
}

bool	ft_heredoc(char *eof, int nbr_eof)
{
	t_heredoc	hrd;
	char		*nb_str;

	ft_bzero(&hrd, sizeof(t_heredoc));
	nb_str = ft_itoa(nbr_eof);
	hrd.filename = ft_strjoin(".EOF", nb_str);
	hrd.id = fork();
	if (hrd.id == 0)
	{
		hrd.fd = open(hrd.filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (hrd.fd == -1)
			return (false);
		ft_doc_ctrl(&hrd, eof, &hrd.fd);
		free(hrd.filename);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(hrd.id, &hrd.status, 0);
	if (hrd.status)
		return (false);
	free(nb_str);
	hrd.fd = open(hrd.filename, O_RDONLY);
	//dup2(hrd.fd, STDIN_FILENO);
	close(hrd.fd);
	free(hrd.filename);
	return (true);
}

// Supprime chaque fichier .EOF(x) créer par le heredoc
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
