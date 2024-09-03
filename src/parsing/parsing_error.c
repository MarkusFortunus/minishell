#include "minishell.h"

int	ft_check_right(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 4 && (str[len - 1] == 't' && str[len - 2] == 'u' && str[len - 3] == 'o' && str[len - 4] == '.'))
	{
		if (access(str, F_OK | X_OK) != 0)
			return (ft_error(str, NULL, ": No such file or directory\n", 127));
	}
	else
		return (ft_error(str, NULL, DIR, 126));
	return (EXIT_SUCCESS);
}

int	ft_check_directory(pipe_cmd_t *node)
{
	int	x;

	x = 0;
	if (node->cmd_arg[0][0] == '/')
	{
		if (access(node->cmd_arg[0], F_OK | X_OK) != 0)
			return (ft_error(node->cmd_arg[0], NULL, ": No such file or directory\n", 127));
		return (ft_error(node->cmd_arg[0], NULL, DIR, 126));
		
		while (node->cmd_arg[0][x])
		{
			if (!ft_strchr("/.", node->cmd_arg[0][x]))
				return (0);
			x++;
		}
		return (ft_error(node->cmd_arg[0], NULL, DIR, 126));
	}
	if (node->cmd_arg[0][0] == '.' && node->cmd_arg[0][1] == '/')
		return (ft_check_right(node->cmd_arg[0]));
	return (0);
}

int	ft_check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			while (str[i] && str[i] != 34)
				i++;
			if (!str[i])
				return (ft_error(NULL, NULL, "missing closing quote\n", 2));
		}
		else if (str[i] == 39)
		{
			while (str[i] && str[i] != 39)
				i++;
			if (!str[i])
				return (ft_error(NULL, NULL, "missing closing quote\n", 2));
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
int	ft_first_check_input(t_data *data)
{
	char	*str;

	str = data->input;
	if ((*str <= 32 || *str == ':' || *str == '#') && ft_strlen(str) == 1)
		return (exit_stat = 0);
	if (*str <= 32 && ft_is_space(str))
		return (exit_stat = 0);
	if (*str == '!' && ft_strlen(str) == 1)
		return (exit_stat = 1);
	if(*str == '|')
	{
		if (*(str + 1) == '|')
			return (ft_error(NULL, NULL, "syntax error near unexpected token '||'\n", 2));
		return (ft_error(NULL, NULL, "syntax error near unexpected token '|'\n", 2));
	}
	return (0);
}

