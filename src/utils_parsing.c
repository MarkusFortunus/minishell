
#include "minishell.h"

void	ft_free_lst(pipe_cmd_t *node)
{
	pipe_cmd_t	*tmp;

	while (node)
	{
		tmp = node;
		node = node-> next;
		if (tmp->stdin_file)
			ft_free(tmp->stdin_file, NULL);
		//if (tmp->env)
		//	ft_free(env, NULL); si on a allouer de la mémoire pour **env
		if (tmp->stdout_file)
			ft_free(tmp->stdout_file, NULL);
		if (tmp->trunc)
			free(tmp->trunc);
		if (tmp->heredoc)
			free(tmp->heredoc);
		free (tmp);
	}
}

int	ft_count_arg(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}