#include "minishell.h"

int	ft_split_arg(pipe_cmd_t *node)
{
	size_t	y;

	y = 0;
	if (node->cmd)
		node->cmd_arg = ft_split_quote(node->cmd, " \t\v\r\f");
	// ft_printf("exit_stat: %d\n", exit_stat);
	if (node->cmd_arg && node->cmd_arg[0])
	{
		// y = 0;
		while (node->cmd_arg[y])
		{
			// ft_printf("cmd_arg: %s\n",node->cmd_arg[y]);
			if (ft_check_quote_dollar(&node->cmd_arg[y], node->env) == 0)
				return (EXIT_FAILURE);
			if (ft_check_directory(node))
				return (exit_stat);
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
	while(file[y])
	{
		if (ft_check_quote_dollar(&file[y], env) == 0)
			return (NULL);
		y++;
	}
	return (file);
}

int	ft_parse_redir(pipe_cmd_t *node)
{
	char	*input;

	input = node->cmd;
	ft_init_redir_node(node);
	if (ft_check_redir_syntax(input, node))
	{
		ft_fill_stdio_file(node, input);
		if (node->trunc)
		{
			// printf("%s\n", node->stdout_file[0]);
			node->stdout_file = ft_remove_quote_in_file(node->stdout_file, node->env);
			if (!node->stdout_file || !node->cmd || !node->stdout_file[0])
				return (ft_error(NULL, NULL, SYNTAX_TOKEN, 2));
		}
		if (node->heredoc)
		{
			node->stdin_file = ft_remove_quote_in_file(node->stdin_file, node->env);
			if (!node->stdin_file || !node->cmd || !node->stdin_file[0])
				return (ft_error(NULL, NULL, SYNTAX_TOKEN, 2));
		}
	}
	else
		return (EXIT_FAILURE);
	if (ft_split_arg(node))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_parse_pipe(t_data *data)
{
	pipe_cmd_t	*arg_lst;
	pipe_cmd_t	*new_node;
	pipe_cmd_t	*cur;
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
