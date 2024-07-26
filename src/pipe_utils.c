#include "minishell.h"

void	close_pipes(int fd[][2], int wichpipe, int nbr_pipe)
{
	int	i;

// tooo dooo checker les redictions quelle ficheir ferme en plus
// ***************************
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

void close_fd(pipe_cmd_t *p_data, t_data *data)
{
	if (p_data->pos == 0) // faire que ca sois aussi pour le in betwee
	{
		if (!p_data->next)
			return ;
		close(data->fd[p_data->pos][1]);
	}
	else
	{
		close(data->fd[p_data->pos - 1][0]);
		close(data->fd[p_data->pos][1]);
	}
	if(!p_data->next)
		close(data->fd[p_data->pos][0]);

}

// mettre p_data-> file_name en array pour avoir les plusieurs rediection
bool stdin_file(pipe_cmd_t *p_data)
{
	int file = 0;

	while (*p_data->stdin_file)
	{
		if (*p_data->stdin_file)
    	{
    	    file = open(*p_data->stdin_file, 0);
    	    if (file == -1 && printf("error failed to open file"))
    	        return false;
    	    if (dup2(file, STDIN_FILENO) == -1 && printf("problem"))
    	        return false;
			close(file);
			p_data->stdin_file++;
			if (*p_data->stdin_file)
				continue;
    	}
		break;		
	}
	return true;
}

bool stdout_file(pipe_cmd_t *p_data)
{
    int file = 0;
	int i = 0;

	while (p_data->stdout_file[i])
	{
		if (p_data->stdout_file[i])
    	{
			if (p_data->trunc[i] == true)
    	    	file = open(p_data->stdout_file[i], O_WRONLY | O_CREAT | O_TRUNC, 777);
			else
				file = open(p_data->stdout_file[i], O_WRONLY | O_CREAT, 777);
    	    if (file == -1 && printf("error failed to open file"))
    	        return false;
    	    if (dup2(file, STDOUT_FILENO) == -1 && printf("problem"))
    	        return false;
			close(file);
			i++;
			if (p_data->stdout_file[i])
				continue;
    	}
		break;		
	}
	return true;
}