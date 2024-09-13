/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:24:09 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/13 16:58:20 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_check_directory(t_pipe_cmd *node)
{
	int	x;

	x = 0;
	if (node->cmd_arg[0][0] == '/')
	{
		while (node->cmd_arg[0][x])
		{
			if (!ft_strchr("/.", node->cmd_arg[0][x]))
				return (0);
			x++;
		}
		return (ft_error(node->cmd_arg[0], NULL, DIR, 126));
	}
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
		return (g_exit_stat = 0);
	if (*str <= 32 && ft_is_space(str))
		return (g_exit_stat = 0);
	if (*str == '!' && ft_strlen(str) == 1)
		return (g_exit_stat = 1);
	if (*str == '|')
	{
		if (*(str + 1) == '|')
			return (ft_error(NULL, NULL,
					"syntax error near unexpected token '||'\n", 2));
		return (ft_error(NULL, NULL, "syntax error near unexpected token '|'\n",
				2));
	}
	return (3);
}
