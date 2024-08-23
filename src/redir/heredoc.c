#include "minishell.h"

static void	ft_doc_ctrl(char *filename, char *eof, int *fd)
{
	char	*line;
	filename = NULL;

	while ((line = get_next_line(0)) != NULL) // readline
	{
		//signal(SIGINT, ft_heredoc_handler); //non testé!!
		//signal(SIGQUIT, SIG_IGN);
		if (!strncmp(line, eof, strlen(eof)) && (line[strlen(eof)] == '\n'
				|| line[strlen(eof)] == '\0'))
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
	free(line);
	if (filename)
	{
		unlink(filename);
		free(filename);
	}
}

bool	ft_heredoc(char *eof, int nbr_eof)
{
	char	*tmp_file;
	char	*filename;
	int		fd;
	int		id;

	id = fork();
	if (id == 0)
	{
		filename = malloc(4 + ft_strlen(ft_itoa(nbr_eof)));
		if (!filename)
			return (free(filename), false);
		tmp_file = malloc(sizeof(ft_strlen(filename)));
		if (!tmp_file)
			free(tmp_file);
		ft_strlcpy(tmp_file, ".EOF", 5);
		filename = ft_strjoin(tmp_file, ft_itoa(nbr_eof));
		free(tmp_file);
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd == -1)
			fprintf(stderr, "erioriror file");
		ft_doc_ctrl(filename, eof, &fd);
	}
	waitpid(id, NULL, 0);
	return (true);
}
