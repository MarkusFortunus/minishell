
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

char	*ft_remove_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			str[i] = ' ';
		i++;
	}
	return (str);
}

	void	ft_parse_redir(pipe_cmd_t *node)
	{
		char	*input;

		input = node->cmd;
		ft_init_redir_node(node);
		ft_check_redir_syntax(input, node);
		if (node->redir_type)
		{
			//print_bool_array(node->trunc, node->stdout_count); //DEBUG
			node->stdout_file = ft_split_quote(node->cmd, "><");
			node->cmd = ft_remove_quote(node->stdout_file[0]);
			if (!node->stdout_file || !node->cmd || !node->stdout_file[1])
				ft_error("syntax error near unexpected token 'newline'\n", 2);
			int i = 0;
			while (node->stdout_file[i])
			{
				ft_printf("%s\n", node->stdout_file[i]);
				i++;
			}
			i = 0;
			while (node->redir_type[i])
			{
				ft_printf("%d\n", node->redir_type[i]);
				i++;
			}
		}
		else
			node->cmd = ft_remove_quote(node->cmd);//ne marche pas ici
		// if (node->heredoc)
		// {
		// 	print_bool_array(node->heredoc, node->stdin_count); //DeBUG
		// 	node->stdin_file = ft_split_quote(node->cmd, "<");
		// 	node->cmd = node->stdin_file[0];
		// 	if (!node->stdin_file || !node->cmd)
		// 		ft_error("syntax error near unexpected token 'newline'\n", 2);
		// 	int i = 0;
		// 	while (node->stdin_file[i])
		// 	{
		// 		ft_printf("%s\n", node->stdin_file[i]);
		// 		i++;
		// 	}
		// }
	}

bool init_pipe(t_data *data)
{
	int i = 0;

	data->fd =  (int (*)[2])malloc((data->arg_count - 1) * sizeof(int [2]));
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
	if (data->arg_count > 1 && !init_pipe(data))
	while (data->args[i])
		i++;
	data->arg_count = i;
	if (data->arg_count > 1 && !init_pipe(data))
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
	int stdout = dup(STDOUT_FILENO);
	int stdin = dup(STDIN_FILENO);
	while (cur)
	{
		if (!each_pipe(cur, data))
			break ; // maybe all the fd wont be close after
		cur = cur->next;
	}
	dup2(stdout, STDOUT_FILENO);
	dup2(stdin, STDIN_FILENO);
	ft_free_lst(arg_lst);
}