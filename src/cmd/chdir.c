/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:12:48 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/13 14:03:48 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chdir_process(char *path)
{
	int	i;

	i = 0;
	if (ft_strchr(path, '.'))
	{
		while (path[i])
			i++;
		if (i == 1)
			return (0);
	}
	if (!path || *path == '\0')
	{
		path = getenv("HOME");
		if (!path)
			return (ft_error("cd: ", NULL, "HOME not set\n", 1));
	}
	if (chdir(path))
		return (ft_error("cd: ", NULL, "No such  file or directory\n", 1));
	return (2);
}

int	ft_chdir(char *path, t_pipe_cmd *node, t_data *data)
{
	char	*tmppwd;
	char	*buf;
	int		return_var;

	buf = malloc(120);
	buf = getcwd(buf, 120);
	tmppwd = ft_strjoin("OLDPWD=", buf);
	ft_export_search(tmppwd, "OLDPWD", node, data);
	free(tmppwd);
	return_var = ft_chdir_process(path);
	if (return_var != 2)
	{
		free(buf);
		return (return_var);
	}
	ft_bzero(buf, 120);
	buf = getcwd(buf, 120);
	tmppwd = ft_strjoin("PWD=", buf);
	ft_export_search(tmppwd, "PWD", node, data);
	free(tmppwd);
	free(buf);
	return (0);
}
