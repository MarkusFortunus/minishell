/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimard <msimard@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:14:02 by fcornill          #+#    #+#             */
/*   Updated: 2024/06/24 14:39:23 by msimard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	ft_export_cmd(t_data *data)
{
	int		y;
	char	*tmp;
	char	**cpy_envp;

	y = 0;
	tmp = NULL;
	cpy_envp = ft_get_envp_cpy(data->envp);

	//if (data->args > 1)// si on a splitter l'input et trouvé plusieurs tokens
		//fonction pour exporter variable
	//else
	while(cpy_envp[y]) //tri a bulle dans le cas ou export est appelé sans args (la commande tri les variables d'env par ordre ascii)
	{
		if (ft_strncmp(cpy_envp[y], cpy_envp[y + 1], 1) > 0)
		{
			tmp = cpy_envp[y];
			cpy_envp[y] = cpy_envp[y + 1];
			cpy_envp[y + 1] = tmp;
			y = 0;
		}
		else
			y++;
	}
	y = 0;
	while (cpy_envp[y])
	{
		ft_printf("%s\n", cpy_envp[y]);
		y++;
	}
	y = 0;
	while (cpy_envp[y])
	{
		free(cpy_envp[y]);
		y++;
	}
	free(cpy_envp);
}