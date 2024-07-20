

#include "minishell.h"

//Fonction qui verifie le type de la commande (Built-in ou executable)

void	ft_check_cmd(t_data *data, pipe_cmd_t *node)
{
	char	**subpath;
	if (data->arg_count == 0)
		return ;
	if (!ft_strncmp(node->cmd, "env", 4))
		ft_env_cmd(data->envp);
	else if (!ft_strncmp(node->cmd, "export", 7))
		ft_export_cmd(data);
	else if (!ft_strncmp(node->cmd, "cd", 3))
	{
		subpath = ft_split_quote(node->cmd, " \t");
		ft_chdir(subpath[1]);// marche pas je crois
		ft_free(subpath, NULL);
	}
	else if (!ft_strncmp(node->cmd, "exit", 5))
		ft_exit_cmd(data);
	else if (!ft_strncmp(node->cmd, "pwd", 4))
		ft_printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(node->cmd, "unset", 6))
		ft_unset(data);
	else
		ft_execute(data->envp, data, node);
}


//Fonction qui execute une commande.
void	ft_execute(char **envp, t_data *data, pipe_cmd_t *node)
{
	char	**cmd_list;
	char	*cmd_path;

	cmd_list = ft_split_quote(node->cmd, " \t");
	printf("First command = %s\n", cmd_list[0]);
	cmd_path = ft_search_path(cmd_list[0], envp);
	data->pid = fork();
	if (data->pid == 0)
	{
		if (!cmd_path)
			ft_error("invalid command\n");
		else
		{
			if (execve(cmd_path, cmd_list, envp) == -1)
				ft_error("Wrong command");
		}
	}
	else
		wait(NULL);
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
