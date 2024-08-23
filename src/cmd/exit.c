#include "minishell.h"

static int	ft_exit_with_arg(t_data *data, pipe_cmd_t *node)
{
	int	exit_val;
	int	x;

	x = 0;
	while (node->cmd_arg[1][x])
	{
		if (!ft_isdigit(node->cmd_arg[1][x]) && \
		node->cmd_arg[1][x] != '+' && node->cmd_arg[1][x] != '-')
		{
			ft_error("exit: ", NULL, "numeric argument required\n", 255);
			ft_free_exit(data, node);
			exit (255);
		}
		x++;
	}
	exit_val = ft_atoi(node->cmd_arg[1]);
	return (exit_val);
}

int	ft_exit_cmd(t_data *data, pipe_cmd_t *node, bool need_exit)
{
	int	exit_val;

	exit_val = 0;
	if (node->cmd_arg[1])
	{
		if (node->cmd_arg[2])
			return (ft_error("exit: ", NULL, "too many arguments\n", 1));
		exit_val = ft_exit_with_arg(data, node);
	}
	if (exit_val > 255)
	{
		exit_status = exit_val - 256;
		if (exit_status > 255)
			exit_status = 255;
	}
	else
		exit_status = exit_val;
	ft_free_exit(data, node);
	exit(exit_status);
	if (need_exit)
		exit (EXIT_SUCCESS);
	ft_free_exit(data, node);
	exit (EXIT_SUCCESS);
}
