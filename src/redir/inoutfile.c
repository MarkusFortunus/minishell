#include "minishell.h"

int	stdin_file(pipe_cmd_t *p_data)
{
	int	file;
	int	i;
	int	eof_nb;

	i = 0;
	file = 0;
	eof_nb = 0;
	// p_data->stdfd = 0;
	// p_data->stdfd = dup(STDIN_FILENO);
	while (p_data->stdin_file[i])
	{
		if (p_data->stdin_file[i])
		{
			if (p_data->heredoc[i] == true)
			{
				if (!ft_heredoc(p_data->stdin_file[i], eof_nb++))
					return (EXIT_FAILURE);
			}
			else
			{
				file = open(p_data->stdin_file[i], O_RDONLY);
				if ((file == -1 && errno == ENOENT && ft_error(p_data->stdin_file[i], NULL, ": No such file or directory\n", 1)) \
					|| (file == -1 && errno == EACCES && ft_error(p_data->stdin_file[i], NULL, ": Permission denied\n", 1)) \
					|| (dup2(file, STDIN_FILENO) == -1 && ft_error(NULL, NULL, "problem pipe\n", 1) && close(file)))
					return (exit_stat);
				close(file);
			}
				i++;
			if (p_data->stdin_file[i])
				continue ;
    	}
		break ;
	}
	return (EXIT_SUCCESS);
}

int	stdout_file(pipe_cmd_t *p_data)
{
    int	file;
	int	i;

	i = 0;
	file = 0;
	while (p_data->stdout_file[i])
	{
		if (p_data->stdout_file[i])
    	{
			if (p_data->trunc[i] == true)
    	    	file = open(p_data->stdout_file[i], O_WRONLY | O_CREAT, 0644);
			else
				file = open(p_data->stdout_file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    	    if ((file == -1 && errno == ENOENT && ft_error(p_data->stdout_file[i], NULL, ": No such file or directory\n", 1)) \
				|| (file == -1 && errno == EACCES && ft_error(p_data->stdin_file[i], NULL, ": Permission denied\n", 1)) \
				|| (dup2(file, STDOUT_FILENO) == -1 && ft_error(NULL, NULL, "problem redirecting pipes\n", 1) && close(file)))
    	        return (exit_stat);
			close(file);
			i++;
			if (p_data->stdout_file[i])
				continue;
    	}
		break;		
	}
	return (EXIT_SUCCESS);
}
