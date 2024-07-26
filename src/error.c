#include "../include/minishell.h"

//Error function, print error message and exit
	void	ft_error(char *error)
	{
		write(2, RED, ft_strlen(RED));
		write(2, "Error:\n", 8);
		write(2, error, ft_strlen(error));
		write(2, RES, ft_strlen(RES));
		exit(1);
	}

void	ft_check_redir_syntax(char *input, pipe_cmd_t *node)
{
	int	i;
	int	out;
	int	in;
	int	trunc_index = 0;
	int	heredoc_index = 0;

	i = 0;
	out = 0;
	in = 0;
	while (input[i])
	{
		if (input[i] == '>')
		{
			out++;
			while (input[++i] == '>')
				out++;
			if (out > 2)
				ft_error("syntax error near unexpected token '>>'\n");
			if (out == 2)
				node->trunc[trunc_index] = true;
			else if (out == 1)
				node->trunc[trunc_index] = false;
			trunc_index++;
			out = 0;
		}
		if (input[i] == '<')
		{
			in++;
			while (input[++i] == '<')
				in++;
			if (in > 2)
				ft_error("syntax error near unexpected token '<<'\n");
			if (in == 2)
				node->heredoc[heredoc_index] = true;
			else if (in == 1)
				node->heredoc[heredoc_index] = false;
			heredoc_index++;
			in = 0;
		}
		i++;
	}
}

//Free un tableau. Exit si un message est ajouter. Sinon, mettre "NULL"
void	ft_free(char **to_free, char *exit)
{
	int	i;

	if (!to_free)
		return ;
	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	if (exit)
		ft_error(exit);
}
