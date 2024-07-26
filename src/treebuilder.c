
#include "minishell.h"

pipe_cmd_t	*ft_init_cmd_node(char *arg, int i, int arg_count)
{
	pipe_cmd_t	*new_node;

	new_node = ft_calloc(1, sizeof(pipe_cmd_t));
	if (!new_node)
		return (NULL);
	(void)arg_count;

	new_node->cmd = arg;
	new_node->pos = i;
	ft_parse_redir(new_node);
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_back(pipe_cmd_t **lst, pipe_cmd_t *new)
{
	pipe_cmd_t	*tmp;

	tmp = *lst;
	if (new == NULL)
		return ;
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_count_redir(char *input, int *in, int *out)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<')
		{
			(*in)++;
			while (input[i] == '<')
				i++;
		}
		else if (input[i] == '>')
		{
			(*out)++;
			while (input[i] == '>')
				i++;
		}
		else
			i++;
	}
}

void	ft_init_redir_node(pipe_cmd_t *node)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	ft_count_redir(node->cmd, &in, &out);
	if (out != 0)
		node->trunc = ft_calloc(out, sizeof(bool));
	if (in != 0)
		node->heredoc = ft_calloc(in, sizeof(bool));
}