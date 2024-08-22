#include "minishell.h"

//Modifie une variable deja existante
void	ft_export_modif(char *export, char ***env)
{
	int		equal_pos;
	char	*line;
	int		i;

	equal_pos = 0;
	find_equal(export, &equal_pos);
	if (equal_pos == -1)
		return ;
	line = malloc(sizeof(char) * (ft_strlen(export) + 1));
	if (!line)
		return ;
	ft_strlcpy(line, export, ft_strlen(export) + 1);
	i = 0;
	while ((*env)[i])
	{
		if (strncmp((*env)[i], export, equal_pos) == 0
			&& (*env)[i][equal_pos] == '=')
		{
			free((*env)[i]);
			(*env)[i] = line;
			return ;
		}
		i++;
	}
}

//add une variable dans l'environement
void	ft_export_add(char *export, char ***env)
{
	char	**new_env;
	int		size_env;
	int		i;

	i = 0;
	size_env = 0;
	while ((*env)[size_env])
		size_env++;
	new_env = malloc((size_env + 2) * sizeof(char *));
	while (i != size_env)
	{
		new_env[i] = ft_strdup((*env)[i]);
		i++;
	}
	new_env[i] = ft_strdup(export);
	i++;
	new_env[i] = NULL;
	ft_free(*env, NULL);
	*env = new_env;
}

//Tri l'environement en ordre alpha
void	ft_export_tri(char **cpy_envp, int y)
{
	char	*tmp;

	while (cpy_envp[y])
	{
		if (ft_strncmp(cpy_envp[y], cpy_envp[y + 1], 1) > 0)
		{
			tmp = cpy_envp[y];
			cpy_envp[y] = cpy_envp[y + 1];
			cpy_envp[y + 1] = tmp;
			y = 0;
		}
		else
			y++;
	}
	y = 0;
	while (cpy_envp[y])
		ft_printf("declare -x %s\n", cpy_envp[y++]);
	y = 0;
}

//Cherche dans l'environement si la variable existe. Si non, la creer
void	ft_export_search(char *exp, char *name, pipe_cmd_t *node, t_data *data)
{
	size_t	i;
	int		x;
	int		flag;

	x = 0;
	flag = 0;
	i = ft_strlen(name);
	while (node->env[x])
	{
		if (ft_strnstr(node->env[x], name, i))
			flag = 1;
		x++;
	}
	if (!flag)
		ft_export_add(exp, &node->env);
	else
		ft_export_modif(exp, &node->env);
	ft_free(data->envp, NULL);
	data->envp = ft_get_envp_cpy(node->env);
}

//Reception de la commande "export" et validation du nom si argc > 1
int	ft_export_cmd(pipe_cmd_t *node, t_data *data)
{
	int		y;
	char	*var_name;
	char 	**env_cpy;

	y = 1;
	env_cpy = ft_get_envp_cpy(node->env);
	if (node->arg_cnt > 1)// si on a splitter l'input et trouvé plusieurs tokens
	{
		while (node->cmd_arg[y]) // to do changer pour cmd arg
		{
			var_name = ft_substr(node->cmd_arg[y], 0, ft_equal_sign(node->cmd_arg[y]));
			if (!ft_valid_name(var_name))
			{
				free(var_name);
				return (ft_error(NULL, NULL, "Not a valid identifier\n", 1));
			}
			ft_export_search(node->cmd_arg[y], var_name, node, data);
			free(var_name);
			y++;
		}
	}
	else
		ft_export_tri(env_cpy, y - 1);
	ft_free(env_cpy, NULL);
	return (0);
}
