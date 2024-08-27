#include "minishell.h"

static void	ft_doc_ctrl(char *filename, char *eof, int *fd)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, ft_heredoc_handler); //non testé!!
		signal(SIGQUIT, SIG_IGN);
		line = get_next_line(0);
		if (!ft_strncmp(line, eof, ft_strlen(eof)) && (line[ft_strlen(eof)] == '\n'
				|| line[ft_strlen(eof)] == '\0'))
			break ;
		else
		{
			write(*fd, line, ft_strlen(line));
			free(line);
		}
	}
	close(*fd);
	*fd = open(filename, O_RDONLY);
	dup2(*fd, 0);
	close(*fd);
	free(line);
	unlink(filename);
	free(filename);
	exit (0);
}

bool	ft_heredoc(char *eof, int nbr_eof)
{
	t_heredoc	hrd;

	ft_bzero(&hrd, sizeof(t_heredoc));
	hrd.id = fork();
	if (hrd.id == 0)
	{
		hrd.filename = malloc(4 + ft_strlen(ft_itoa(nbr_eof)));
		if (!hrd.filename)
			return (free(hrd.filename), false);
		hrd.tmp_file = malloc(sizeof(ft_strlen(hrd.filename)));
		if (!hrd.tmp_file)
			free(hrd.tmp_file);
		ft_strlcpy(hrd.tmp_file, ".EOF", 5);
		hrd.filename = ft_strjoin(hrd.tmp_file, ft_itoa(nbr_eof));
		free(hrd.tmp_file);
		hrd.fd = open(hrd.filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (hrd.fd == -1)
			return (false);
		ft_doc_ctrl(hrd.filename, eof, &hrd.fd);
	}
	waitpid(hrd.id, &hrd.status, 0);
	if (hrd.status)
		return (false);
	return (true);
}
