/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimard <msimard@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:13:16 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/10 20:29:44 by msimard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_loop(t_pipe_cmd *node, int i)
{
	while (node->cmd_arg[i])
	{
		if (ft_strlen(node->cmd_arg[i]) != 0)
		{
			if (node->cmd_arg[i + 1] == NULL)
				ft_printf("%s", node->cmd_arg[i]);
			else
				ft_printf("%s ", node->cmd_arg[i]);
		}
		i++;
	}
}

static bool	ft_echo_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-' && str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(t_pipe_cmd *node)
{
	bool	flag;
	int		i;

	i = node->x + 1;
	flag = false;
	if (node->arg_cnt == 1)
	{
		ft_printf("\n");
		return (0);
	}
	if (!ft_strncmp(node->cmd_arg[i], "-n", 2))
	{
		while (node->cmd_arg[i])
		{
			if (ft_echo_check(node->cmd_arg[i]) == true)
				i++;
			else
				break ;
		}
		flag = true;
	}
	ft_echo_loop(node, i);
	if (flag == false)
		ft_printf("\n");
	return (0);
}
