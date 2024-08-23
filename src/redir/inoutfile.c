#include "minishell.h"

bool stdin_file(pipe_cmd_t *p_data)
{
	int file = 0;
	int	i = 0;
	int	eof_nb;

	eof_nb = 0;
	while (*p_data->stdin_file)
	{
		if (*p_data->stdin_file)
    	{
			if (p_data->heredoc[i] == true)
				ft_heredoc(p_data->stdin_file[i], eof_nb++);
			else
			{
				file = open(*p_data->stdin_file, O_RDONLY);
    	    	if ((file == -1 && ft_error(*p_data->stdin_file, NULL, ": No such file or directory\n", 1)) \
					|| (dup2(file, STDIN_FILENO) == -1 && ft_error(NULL, NULL, "problem pipe", 1) && close(file)))
    	        	return false;
				close(file);
			}
				p_data->stdin_file++;
			if (*p_data->stdin_file)
				continue ;
    	}
		break;		
	}
	return (true);
}

bool stdout_file(pipe_cmd_t *p_data)
{
    int file = 0;
	int i = 0;

	while (p_data->stdout_file[i])
	{
		if (p_data->stdout_file[i])
    	{
			// fprintf(stderr, "trunc %i\n", p_data->trunc[i]);
			if (p_data->trunc[i] == true)
    	    	file = open(p_data->stdout_file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				file = open(p_data->stdout_file[i], O_WRONLY | O_CREAT, 0644);
    	    if ((file == -1 && ft_error(*p_data->stdout_file, NULL, ": No such file or directory\n", 1)) \
				|| (dup2(file, STDOUT_FILENO) == -1 && ft_error(NULL, NULL, "problem redirecting pipes", 1) && close(file)))
    	        return (false);
			close(file);
			i++;
			if (p_data->stdout_file[i])
				continue;
    	}
		break;		
	}
	return true;
}
