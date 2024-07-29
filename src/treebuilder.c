
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
		if (input[i] == '\'' || input[i] == '"') // Check for quotes
		{
			input = ft_skip_quote(&input[i]); // Skip the quoted part
			i = input - input; // Adjust the index
		}
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
	ft_count_redir(node->cmd, &node->stdin_count, &node->stdout_count);
	if (node->stdout_count != 0)
		node->trunc = ft_calloc(node->stdout_count, sizeof(bool));
	if (node->stdin_count != 0)
		node->heredoc = ft_calloc(node->stdin_count, sizeof(bool));
	if (node->stdout_count > 0 || node-> stdin_count > 0)
		node->redir_type = ft_calloc(node->stdout_count + node->stdin_count + 1, sizeof(int));// +1 sinon redir_index ds ft_check_redir_syntax depasse la memoire autorisé
	ft_printf("%d\n", node->stdout_count + node->stdin_count);
}