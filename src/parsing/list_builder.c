/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:23:05 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 15:23:12 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe_cmd	*ft_init_cmd_node(char *arg, int i, t_pipe_cmd *st_lst,
		t_data *data)
{
	t_pipe_cmd	*new_node;

	new_node = ft_calloc(1, sizeof(t_pipe_cmd));
	new_node->cmd = ft_strdup(arg);
	if (!new_node || !new_node->cmd)
		return (NULL);
	new_node->pos = i;
	new_node->env = ft_get_envp_cpy(data->envp);
	new_node->next = NULL;
	new_node->start_ls = st_lst;
	if (ft_parse_redir(new_node, new_node->cmd))
	{
		ft_free(data->args, NULL);
		ft_free_lst(new_node);
		return (NULL);
	}
	return (new_node);
}

void	ft_add_back(t_pipe_cmd **lst, t_pipe_cmd *new)
{
	t_pipe_cmd	*tmp;

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

void	ft_init_redir_node(t_pipe_cmd *node)
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
