/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimard <msimard@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:21:28 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/16 14:05:08 by msimard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_search_loop(char **all_paths, char *command, int i)
{
	char	*tmp_path;
	char	*true_path;

	while (all_paths[i])
	{
		tmp_path = ft_strjoin(all_paths[i], "/");
		true_path = ft_strjoin(tmp_path, command);
		free(tmp_path);
		if (access(true_path, F_OK) == 0)
			return (true_path);
		free(true_path);
		i++;
	}
	ft_free(all_paths, NULL);
	return (NULL);
}

char	*ft_search_path(char *command, char **envp)
{
	char	**all_paths;
	int		i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (access(command, F_OK) == 0)
		return (command);
	if (!envp[i])
		return (NULL);
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	return (ft_search_loop(all_paths, command, i));
}
