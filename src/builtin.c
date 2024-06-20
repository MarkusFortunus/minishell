/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:01:59 by fcornill          #+#    #+#             */
/*   Updated: 2024/06/20 10:10:45 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_cmd(char **envp)
{
	int	y;
	
	y = 0;
	while (envp[y])
	{
		ft_printf("%s\n", envp[y]);
		y++;
	}
}

void	exit_cmd(t_data *data)
{
	free(data->input);//sinon leaks dansle cas ou on ne tape de commande valide
	free(data);
	exit (EXIT_SUCCESS);
}

void	pwd_cmd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}