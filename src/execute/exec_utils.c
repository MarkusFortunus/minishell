/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:21:28 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/26 13:52:38 by fcornill         ###   ########.fr       */
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

int	ft_is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

char	*ft_search_path(char *command, char **envp)
{
	char **all_paths;
	int i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (access(command, F_OK) == 0 && access(command, X_OK) == 0)
	{
		if (is_directory(command))
		{
			errno = EISDIR;
			return (NULL);
		}
		return (command);
	}
	if (!envp[i])
		return (NULL);
	all_paths = ft_split(envp[i] + 5, ':');
	return (ft_search_loop(all_paths, command, 0));
}
