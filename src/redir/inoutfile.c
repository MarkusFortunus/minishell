#include "minishell.h"

static int open_redir(char *stdfile, bool isstdin, bool istrunc)
{
	int	file;

	file = 0;
	if (isstdin)
	{
		file = open(stdfile, O_RDONLY);
		if ((file == -1 && errno == ENOENT && ft_error(stdfile, NULL, ": No such file or directory\n", 1)) \
		|| (file == -1 && errno == EACCES && ft_error(stdfile, NULL, ": Permission denied\n", 1)) \
		|| (dup2(file, STDIN_FILENO) == -1 && ft_error(NULL, NULL, "problem pipe\n", 1)))
				return (exit_stat);
		
	}
	else
	{
		if (istrunc == true)
    		file = open(stdfile, O_WRONLY | O_CREAT, 0644);
		else
			file = open(stdfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    	if ((file == -1 && errno == ENOENT && ft_error(stdfile, NULL, ": No such file or directory\n", 1)) \
			|| (file == -1 && errno == EACCES && ft_error(stdfile, NULL, ": Permission denied\n", 1)) \
			|| (dup2(file, STDOUT_FILENO) == -1 && ft_error(NULL, NULL, "problem redirecting pipes\n", 1) && close(file)))
    	    	return (exit_stat);
	}
	close(file);
	return (-1);
}

int	stdin_file(pipe_cmd_t *p_data)
{
	int	i;
	int	eof_nb;

	i = 0;
	eof_nb = 0;
	while (p_data->stdin_file[i])
	{
		if (p_data->stdin_file[i])
		{
			if (p_data->heredoc[i] == true)
			{
				if (!ft_heredoc(p_data->stdin_file[i], eof_nb++))
					return (EXIT_FAILURE);
			}
			else if (open_redir(p_data->stdin_file[i], true, false) == exit_stat)
				return (exit_stat);
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
	int	i;

	i = 0;
	while (p_data->stdout_file[i])
	{
		if (p_data->stdout_file[i])
    	{
			if (open_redir(p_data->stdout_file[i], false, p_data->trunc[i]) == exit_stat)
				return (exit_stat);
			i++;
			if (p_data->stdout_file[i])
				continue;
    	}
		break;		
	}
	return (EXIT_SUCCESS);
}
