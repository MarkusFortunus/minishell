/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:14:27 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 15:17:02 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	remov_var(t_pipe_cmd *node, t_data *data, int i, int j)
{
	if (ft_strncmp(node->env[i], node->cmd_arg[j], ft_strlen(node->cmd_arg[j]))
		|| node->env[i][ft_strlen(node->cmd_arg[j])] != '=')
		return (false);
	while (node->env[i + 1])
	{
		free(node->env[i]);
		node->env[i] = ft_strdup(node->env[i + 1]);
		if (!node->env[i] && printf("Error with allocing memory\n"))
			return (false);
		i++;
	}
	free(node->env[i]);
	node->env[i] = ft_strdup(NULL);
	free(node->env[i + 1]);
	ft_free(data->envp, NULL);
	data->envp = ft_get_envp_cpy(node->env);
	return (true);
}

void	ft_unset(t_pipe_cmd *node, t_data *data)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (node->cmd_arg[j])
	{
		while (node->env[i])
		{
			if (remov_var(node, data, i, j))
				break ;
			i++;
		}
		i = 0;
		j++;
	}
}
