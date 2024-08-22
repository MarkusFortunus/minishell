#include "minishell.h"

int	ft_exit_cmd(t_data *data, pipe_cmd_t *node, bool need_exit)
{
	//use node
	int	exit_val;
	int	x;

	exit_val = 0;
	x = 0;
	(void)data; //debug
	// if (data->arg_count > 1)
	// {
	// 	free(data->fd);
	// 	ft_free_lst(node->start_ls);
	// }
	// // else
	// // 	ft_free_lst(node);
	// free(data->input);//sinon leaks dans le cas ou on ne tape de commande valide
	// ft_free_data(data);
	if (node->cmd_arg[1])
	{
		if (node->cmd_arg[2])
			return (ft_error("exit: ", NULL, "too many arguments\n", 1));
		while (node->cmd_arg[1][x])
		{
			if(!ft_isdigit(node->cmd_arg[1][x]))
			{
				ft_error("exit: ", NULL, "numeric argument required\n", 255);
				exit (255);
			}
			x++;
		}
		exit_val = ft_atoi(node->cmd_arg[1]);
		if (exit_val > 255)
		{
			exit_status = exit_val - 256;
			if (exit_status > 255)
				exit_status = 255;
		}
		else
			exit_status = exit_val;
		exit(exit_status);
	}
	if (need_exit)
		exit (EXIT_SUCCESS);
	exit (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
