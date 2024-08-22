#include "minishell.h"

void	close_pipes(int fd[][2], int wichpipe, int nbr_pipe)
{
	int	i;

	if (wichpipe == 0)
	{
		i = 1;
		close(fd[0][0]);
		while (i < nbr_pipe)
		{
			close(fd[i][0]);
			close(fd[i][1]);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < nbr_pipe)
		{
			if (wichpipe != i + 1)
				close(fd[i][0]);
			if (wichpipe != i)
				close(fd[i][1]);
			i++;
		}
	}
}
