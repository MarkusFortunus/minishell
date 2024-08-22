#include "minishell.h"

static void	ft_doc_ctrl(char *filename, char *eof, int *fd)
{
	char	*line;

	while ((line = get_next_line(0)) != NULL) // readline
	{
		signal(SIGINT, ft_heredoc_handler); //non testé!!
		signal(SIGQUIT, SIG_IGN);
		if (!strncmp(line, eof, strlen(eof)) && (line[strlen(eof)] == '\n'
				|| line[strlen(eof)] == '\0'))
			break ;
		else
			write(*fd, line, ft_strlen(line));
	}
	close(*fd);
	*fd = open(filename, O_RDONLY);
	dup2(*fd, 0);
	free(line);
	if (filename)
		unlink(filename);
	free(filename);
	// signal(SIGINT, ft_handle_sigint);
}

bool	ft_heredoc(char *eof, int nbr_eof)
{
	char	*tmp_file;
	char	*filename;
	int		fd;

	filename = malloc(4 + ft_strlen(ft_itoa(nbr_eof)));
	if (!filename)
		return (free(filename), false);
	tmp_file = malloc(sizeof(filename));
	if (!tmp_file)
		free(tmp_file);
	ft_strlcpy(tmp_file, ".EOF", 5);
	filename = ft_strjoin(tmp_file, ft_itoa(nbr_eof));
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		fprintf(stderr, "erioriror file");
	ft_doc_ctrl(filename, eof, &fd);
	return (true);
}
