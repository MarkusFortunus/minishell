/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimard <msimard@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:03:55 by msimard           #+#    #+#             */
/*   Updated: 2024/06/25 22:09:13 by msimard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Fonction qui verifie le type de la commande (Built-in ou executable)
void	ft_check_cmd(t_data *data)
{
	pid_t	pid;

	pid = fork();
	waitpid(pid, NULL, 0);
	if (pid == 0)
	{
		if (ft_strncmp(data->input, "env", 3) == 0)
			ft_env_cmd(data->envp);
		if (ft_strncmp(data->input, "export", 6) == 0)
			ft_export_cmd(data);
		//if (ft_strncmp(data->input, "pwd", 3) == 0)
		//	ft_pwd_cmd();
		else
			ft_execute(data->input, data->envp);
	}
	if (ft_strncmp(data->input, "exit", 4) == 0)
		ft_exit_cmd(data);
}

//Fonction qui execute une commande.
void	ft_execute(char *commands, char **envp)
{
	char	**cmd_list;
	char	*cmd_path;

	cmd_list = ft_split(commands, ' ');
	cmd_path = ft_search_path(cmd_list[0], envp);
	if (!cmd_path)
	{
		ft_isbuilt(cmd_list);
	}
	else if (execve(cmd_path, cmd_list, envp) == -1)
		ft_error("Wrong command");
}

//Fonction pour trouver le chemin d'un excutable.
char	*ft_search_path(char *command, char **envp)
{
	char	**all_paths;
	char	*true_path;
	char	*tmp_path;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
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
	return (0);
}

//Fonction pour executer une commande implementer dans l'ordi.
void	ft_isbuilt(char **list)
{
	char	*path;
	int		i;

	i = 0;
	while (list[i])
	{
		path = list[i];
		if (!ft_strncmp(list[i], "cd", 2))
			chdir(list[++i]);
		if (!ft_strncmp(list[i], "pwd", 3))
			ft_printf("%s\n", getcwd(NULL, 0));
		i++;
	}
}