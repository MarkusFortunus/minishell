#include "minishell.h"

pipe_cmd_t	*ft_init_cmd_node(char *arg, int i, pipe_cmd_t *st_lst, t_data *data)
{
	pipe_cmd_t	*new_node;

	new_node = ft_calloc(1, sizeof(pipe_cmd_t));
	new_node->cmd = ft_strdup(arg);
	if (!new_node || !new_node->cmd)
		return (NULL);
	new_node->pos = i;
	new_node->env = ft_get_envp_cpy(data->envp);
	new_node->next = NULL;
	new_node->start_ls = st_lst;
	if (ft_parse_redir(new_node))
	{
		ft_free_lst(new_node);
		return (NULL);
	}
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
		if (input[i] == '\'' || input[i] == '"')
			i = ft_skip_quote(&input[i]) - input;
		if (input[i] && input[i] == '<')
		{
			(*in)++;
			while (input[i] == '<')
				i++;
		}
		else if (input[i] && input[i] == '>')
		{
			(*out)++;
			while (input[i] == '>')
				i++;
		}
		else if (input[i])
			i++;
	}
}

void	ft_init_redir_node(pipe_cmd_t *node)
{
	ft_count_redir(node->cmd, &node->stdin_count, &node->stdout_count);
	if (node->stdout_count != 0)
	{
		node->trunc = ft_calloc(node->stdout_count, sizeof(bool));
		node->stdout_file = ft_calloc(node->stdout_count + 1, sizeof(char *));
	}
	else
		node->stdout_file = ft_calloc(1, sizeof(char *));
	if (node->stdin_count != 0)
	{
		node->heredoc = ft_calloc(node->stdin_count, sizeof(bool));
		node->stdin_file = ft_calloc(node->stdin_count + 1, sizeof(char *));
	}
	else
		node->stdin_file = ft_calloc(1, sizeof(char *));
}
