/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimard <msimard@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:01:59 by fcornill          #+#    #+#             */
/*   Updated: 2024/06/25 21:25:36 by msimard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env_cmd(char **envp)
{
	int	y;
	
	y = 0;
	while (envp[y])
	{
		ft_printf("%s\n", envp[y]);
		y++;
	}
}

void	ft_exit_cmd(t_data *data)
{
	free(data->input);//sinon leaks dansle cas ou on ne tape de commande valide
	free(data);
	exit (EXIT_SUCCESS);
}

void	ft_pwd_cmd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}