/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:03:55 by msimard           #+#    #+#             */
/*   Updated: 2024/06/19 14:26:36 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_cmd(t_data *data)
{
	if (ft_strncmp(data->input, "env", 3) == 0)
		env_cmd(data->envp);
	if (ft_strncmp(data->input, "export", 6) == 0)
		export_cmd(data);
	if (ft_strncmp(data->input, "exit", 4) == 0)
		exit_cmd(data);
	if (ft_strncmp(data->input, "pwd", 3) == 0)
		pwd_cmd();
}

