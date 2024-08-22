
#include "minishell.h"

int	ft_check_directory(pipe_cmd_t *node)
{
	int	x;

	x = 0;
	if (node->cmd_arg[0][0] == '/')
	{
		if (ft_strlen(node->cmd_arg[0]) == 1 || \
		(node->cmd_arg[0][1] == '/' || \
		(node->cmd_arg[0][1] == '.' && ft_strlen(node->cmd_arg[0]) == 2)))
			return (ft_error(node->cmd_arg[0], NULL, ": is a directory\n", 126));
		else
		{
			while (node->cmd_arg[0][x])
			{
				if (!ft_strchr("/.", node->cmd_arg[0][x]))
					return (0);
				x++;
			}
			return (ft_error(node->cmd_arg[0], NULL, ": is a directory\n", 126));
		}
	}
	return (0);
}

int	ft_check_quote(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == 34)
		{
			while (str[i] && str[i] != 34)
				i++;
			if (!str[i])
			{
				ft_error(NULL, NULL, "missing closing quote\n", 2);
				return (EXIT_FAILURE);
			}
		}
		else if (str[i] == 39)
		{
			while (str[i] && str[i] != 39)
				i++;
			if (!str[i])
			{
				ft_error(NULL, NULL, "missing closing quote\n", 2);
				return (EXIT_FAILURE);
			}
		}
		i++;
	} 
	return (EXIT_SUCCESS);
}

int	ft_check_pipe(t_data *data)
{
	int	y;

	y = 0;
	if (ft_check_quote(data->input))
		return (ft_free_data(data), EXIT_FAILURE);
	if (!data->args)
	{
		ft_error(NULL, NULL, "syntax error near unexpected token '|'\n", 2);
		return (EXIT_FAILURE);
	}
	while (data->args[y])
	{
			if (ft_is_space(data->args[y]))
			{
				ft_error(NULL, NULL, "syntax error near unexpected token '|'\n", 2);
				return (EXIT_FAILURE);
			}
		y++;
	}
	return (EXIT_SUCCESS);
}