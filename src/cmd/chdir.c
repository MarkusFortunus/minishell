/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:12:48 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 15:12:55 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chdir(char *path, t_pipe_cmd *node, t_data *data)
{
	char	*buf;
	int		i;

	i = 0;
	buf = malloc(120);
	buf = getcwd(buf, 120);
	ft_export_search(ft_strjoin("OLDPWD=", buf), "OLDPWD", node, data);
	if (ft_strchr(path, '.'))
	{
		while (path[i])
			i++;
		if (i == 1)
			return (0);
	}
	if (chdir(path))
		return (ft_error("cd: ", NULL, "No such  file or directory\n", 1));
	ft_bzero(buf, 120);
	buf = getcwd(buf, 120);
	ft_export_search(ft_strjoin("PWD=", buf), "PWD", node, data);
	return (0);
}
