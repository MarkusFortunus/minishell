

#include "minishell.h"

//Fonction qui verifie le type de la commande (Built-in ou executable)

bool	ft_check_cmd(t_data *data, pipe_cmd_t *node)
{
	//char	**subpath; // si plus facile pour chdir et autre commande, on peut splitter 
	//node->cmd ici pour avoir un tableau avec cmd et args séparé et envoyer ça à ft_execute
	if (data->arg_count == 0)
		return true;
	if (!ft_strncmp(node->cmd, "env", 4))
		ft_env_cmd(data->envp);
	else if (!ft_strncmp(node->cmd, "export ", 7))
		ft_export_cmd(data);
	else if (!ft_strncmp(node->cmd, "cd ", 3))
		ft_chdir(node->cmd);
	else if (!ft_strncmp(node->cmd, "exit ", 5))
		ft_exit_cmd(data);
	else if (!ft_strncmp(node->cmd, "pwd ", 4))
		ft_printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(node->cmd, "unset ", 6))
		ft_unset(data);
	else
		return ft_execute(data->envp, data, node);
	return false;
}

//Fonction qui execute une commande.
bool	ft_execute(char **envp, t_data *data, pipe_cmd_t *node)
{ (void)data;
	char	**cmd_list;
	char	*cmd_path;
	// int		status;

	cmd_list = ft_split_quote(node->cmd, " \t");
	cmd_path = ft_search_path(cmd_list[0], envp);
	data->pid = fork();
	signal(SIGINT, ft_child_handle_signal);
	signal(SIGQUIT, ft_child_handle_signal);
	if (data->pid == 0)
	{
		if (execve(cmd_path, cmd_list, envp) == -1)
			ft_error("Wrong command\n");
	}
	return false;
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
	return (NULL);
}

//Premiere tentative de heredoc trouver.
// int	here_doc(t_data *data)
// {
// 	char	*line;
// 	char	*tmp;

// 	if (pipe(data->fd) == -1)
// 		return (-1);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (ft_strcmp(line, data->args[1]) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		tmp = ft_strjoin(line, "\n");
// 		write(data->fd[1], tmp, ft_strlen(tmp));
// 		free(line);
// 		free(tmp);
// 	}
// 	close(data->fd[1]);
// 	return (data->fd[0]);
// }