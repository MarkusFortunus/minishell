/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onault <onault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:23:40 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 16:00:21 by onault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_arg(t_pipe_cmd *node)
{
	size_t	y;

	y = 0;
	if (node->cmd)
		node->cmd_arg = ft_split_quote(node->cmd, " \t\v\r\f");
	if (node->cmd_arg && node->cmd_arg[0])
	{
		while (node->cmd_arg[y])
		{
			if (ft_check_quote_dollar(&node->cmd_arg[y], node->env) == 0)
				return (EXIT_FAILURE);
			if (ft_check_directory(node))
				return (g_exit_stat);
			y++;
		}
		node->arg_cnt = y;
	}
	return (EXIT_SUCCESS);
}

char	**ft_remove_quote_in_file(char **file, char **env)
{
	size_t	y;

	y = 0;
	while (file[y])
	{
		if (ft_check_quote_dollar(&file[y], env) == 0)
			return (NULL);
		y++;
	}
	return (file);
}

int	ft_parse_redir(t_pipe_cmd *node, char *input)
{
	ft_init_redir_node(node);
	if (ft_check_redir_syntax(input, node))
	{
		ft_fill_stdio_file(node, input);
		if (node->trunc)
		{
			node->stdout_file = ft_remove_quote_in_file(node->stdout_file,
					node->env);
			if (!node->stdout_file)
				return (EXIT_FAILURE);
			if (!node->cmd || !node->stdout_file[0])
				return (ft_error(NULL, NULL, SYNTAX_TOKEN, 2));
		}
		if (node->heredoc)
		{
			node->stdin_file = ft_remove_quote_in_file(node->stdin_file,
					node->env);
			if (!node->stdin_file || !node->cmd || !node->stdin_file[0])
				return (ft_error(NULL, NULL, SYNTAX_TOKEN, 2));
		}
		if (ft_split_arg(node))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_parse_pipe(t_data *data)
{
	t_pipe_cmd	*arg_lst;
	t_pipe_cmd	*new_node;
	t_pipe_cmd	*cur;
	int			i;

	arg_lst = NULL;
	data->arg_count = ft_count_arg(data->args);
	i = 0;
	while (data->args[i])
	{
		new_node = ft_init_cmd_node(data->args[i], i, arg_lst, data);
		if (new_node)
			ft_add_back(&arg_lst, new_node);
		else
			return (EXIT_FAILURE);
		i++;
	}
	cur = arg_lst;
	start_pipe(cur, data);
	ft_delete_hrd_file();
	ft_free(data->args, NULL);
	ft_free_lst(arg_lst);
	return (EXIT_SUCCESS);
}

bool	start_pipe(t_pipe_cmd *p_data, t_data *data)
{
	if (data->arg_count == 1 && is_builtin(p_data))
	{
		p_data->stdin = dup(STDIN_FILENO);
		p_data->stdout = dup(STDOUT_FILENO);
		g_exit_stat = ft_do_cmd(p_data, data);
		if (dup2(p_data->stdin, STDIN_FILENO) != -1)
			close(p_data->stdin);
		if (dup2(p_data->stdout, STDOUT_FILENO) != -1)
			close(p_data->stdout);
	}
	else
		each_pipe(p_data, data);
	return (true);
}
