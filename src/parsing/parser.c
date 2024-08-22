
#include "minishell.h"

// static void print_bool_array(bool *array, int size) {
//     printf("[");
//     for (int i = 0; i < size; i++) {
//         printf("%s", array[i] ? "true" : "false");
//         if (i < size - 1) {
//             printf(", ");
//         }
//     }
//     printf("]\n");
// }

int	ft_split_arg(pipe_cmd_t *node)
{
	// int i;
	if (node->cmd)	
		node->cmd_arg = ft_split_quote(node->cmd, " \t\v\r\f\n");
	// if (node->cmd_arg[0][0] == '\n')// commenter et tester en separateur pour voir si MARCHE POUR RENVOYER ANCIEN CODE ERREUR
	// 	return (exit_status);
	if (node->cmd_arg && node->cmd_arg[0])
	{
		if (ft_check_directory(node))
			return (exit_status);
		int y = 0;
		while (node->cmd_arg[y])
		{
			if (ft_check_quote_dollar(&node->cmd_arg[y], node->env) == 0)
				return (EXIT_FAILURE);
			// ft_printf("str : %s\n", node->cmd_arg[y]);
			y++;
		}
		node->arg_cnt = y;
	}
	return (EXIT_SUCCESS);
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
			// print_bool_array(node->trunc, node->stdout_count); //DEBUG
			if (!node->stdout_file || !node->cmd || !node->stdout_file[0])
			{
				ft_error(NULL, NULL, "syntax error near unexpected token 'newline'\n", 2);
				return (1);
			}
			// int i = 0;
			// while (node->stdout_file[i])
			// {
			// 	ft_printf("stdout: %s\n", node->stdout_file[i]);
			// 	i++;
			// }
		}
		if (node->heredoc)
		{
			// print_bool_array(node->heredoc, node->stdin_count); //DeBUG
			if (!node->stdin_file || !node->cmd || !node->stdin_file[0])
			{
				ft_error(NULL, NULL, "syntax error near unexpected token 'newline'\n", 2);
				return (1);
			}
			// int i = 0;
			// while (node->stdin_file[i])
			// {
			// 	ft_printf("eof: %s\n", node->stdin_file[i]);
			// 	i++;
			// }
		}
	}
	else
		return (EXIT_FAILURE);
	if (ft_split_arg(node))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool init_pipe(t_data *data)
{
	int i = 0;

	data->fd =  ft_calloc((data->arg_count - 1), sizeof(int [2]));
	if (!data->fd)
	{
		printf("error malloc\n");
		return false;
	}
	while (i < data->arg_count - 1)
	{
		if (pipe(data->fd[i]) == -1 && printf("problem\n"))
			return false;
		i++;
	}
	return true;
}

int	ft_parse_pipe(t_data *data)
{
	int		i;
	pipe_cmd_t	*new_node;
	pipe_cmd_t	*arg_lst = NULL;
	pipe_cmd_t	*cur;

	data->arg_count = ft_count_arg(data->args);
	// printf("arg count %i\n", data->arg_count);
	if (data->arg_count > 1 && !init_pipe(data))
		return (EXIT_FAILURE);
	i = 0;
	while (data->args[i])
	{
		new_node = ft_init_cmd_node(data->args[i], i, arg_lst, data); //parse_redir ici
		if (new_node)
			ft_add_back(&arg_lst, new_node);
		else
			return (EXIT_FAILURE);
		i++;
	}
	cur = arg_lst;
	start_pipe(cur, data);
	ft_free_lst(arg_lst);
	return (EXIT_SUCCESS);
}