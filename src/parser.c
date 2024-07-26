
#include "minishell.h"

	void	ft_parse_redir(pipe_cmd_t *node)
	{
		char	*input;

		input = node->cmd;
		ft_init_redir_node(node);
		ft_check_redir_syntax(input, node);
		if (node->trunc)
		{
			node->stdout_file = ft_split_quote(node->cmd, ">");
			node->cmd = node->stdout_file[0];
			if (!node->stdout_file || !node->cmd)
				ft_error("syntax error near unexpected token 'newline'\n");
			int i = 0;
			while (node->stdout_file[i])
			{
				ft_printf("%s\n", node->stdout_file[i]);
				i++;
			}
			ft_printf("commande: %s\n", node->cmd);
		}
		if (node->heredoc)
		{
			node->stdin_file = ft_split_quote(node->cmd, "<");
			node->cmd = node->stdin_file[0];
			if (!node->stdin_file || !node->cmd)
				ft_error("syntax error near unexpected token 'newline'\n");
			ft_printf("commande: %s\n", node->cmd);
		}
	}

bool init_pipe(t_data *data)
{
	int i = 0;

	data->fd =  (int (*)[2])malloc((data->arg_count - 1) * sizeof(int [2]));
	// data->fd = (int (*)[2])malloc((data->arg_count - 1) * sizeof(int [2]));

	if (!data->fd)
	{
		printf("error malloc\n");
		return false;
	}
	printf(" yoyoy %i\n\n", data->arg_count);
	while (i < data->arg_count - 1)
	{
		if (pipe(data->fd[i]) == -1 && printf("problem\n"))
			return false;
		i++;
	}
	return true;
}

void	ft_parse_pipe(t_data *data)
{
	int		i;
	pipe_cmd_t	*new_node;
	pipe_cmd_t	*arg_lst = NULL;
	pipe_cmd_t	*cur;
	i = 0;
	// nbr argc;
	// while (data->args[i])
	// 	i++;
	data->arg_count = ft_count_arg(data->args);
	printf("arg count %i\n", data->arg_count);

	if (data->arg_count != 1 && !init_pipe(data))
		return ;
	i = 0;
	while (data->args[i])
	{
		new_node = ft_init_cmd_node(data->args[i], i, data->arg_count);
		if (new_node)
			ft_add_back(&arg_lst, new_node);
		i++;
	}
	cur = arg_lst;
		while (cur)
		{
			if (!cur->next)
				cur->stdout = dup(STDOUT_FILENO);
			printf("pipe %i\n", cur->pos);
			each_pipe(cur, data);
			//ft_check_cmd(data, cur); // *****************utiliser le check command dans pipe
			cur = cur->next;
		}
	printf("%s\n", cur->cmd);
	int stdout = dup(STDOUT_FILENO);
	int stdin = dup(STDIN_FILENO);

	while (cur)
	{
		printf("pipe %i\n\n", cur->pos);
		each_pipe(cur, data);
		cur = cur->next;
	}
	dup2(stdout, STDOUT_FILENO);
	dup2(stdin, STDIN_FILENO);
	ft_free_lst(arg_lst);
}