

#include "minishell.h"

//Modifie une variable deja existante
void	ft_export_modif(char *export, char **env_cpy, t_data *data)
{
	printf("I get in modif\n");
	data = NULL;
	env_cpy = NULL;
	export = NULL;
}

//add une variable dans l'environement
void	ft_export_add(char *export, char **env_cpy, t_data *data)
{
	printf("I get in add\n");
	data = NULL;
	env_cpy = NULL;
	export = NULL;
}

//Tri l'environement en ordre alpha
void	ft_export_tri(char **cpy_envp, int y)
{
	char	*tmp;


	while(cpy_envp[y]) //tri a bulle dans le cas ou export est appelé sans args (la commande tri les variables d'env par ordre ascii)
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
	ft_free(cpy_envp, NULL);
}

//Cherche dans l'environement si la variable existe. Si non, la creer
void	ft_export_search(char *export, char *name, char **env_cpy, t_data *data)
{
	size_t	i;
	int		x;
	int		flag;

	x = 0;
	flag = 0;
	i = ft_strlen(name);
	while (env_cpy[x])
	{
		if (ft_strnstr(env_cpy[x], name, i))
			flag = 1;
		x++;
	}
	if (!flag)
		ft_export_add(export, env_cpy, data);
	else
		ft_export_modif(export, env_cpy, data);
}

//Reception de la commande "export" et validation du nom si argc > 1
void	ft_export_cmd(t_data *data)
{
	int		y;
	char	*var_name;
	char	**cpy_envp;

	y = 1;
	cpy_envp = ft_get_envp_cpy(data->envp);
	if (data->arg_count > 1)// si on a splitter l'input et trouvé plusieurs tokens
	{
		while (data->args[y])
		{
			var_name = ft_substr(data->args[y], 0, ft_equal_sign(data->args[y]));
			if (!ft_valid_name(var_name))
			{
				free(var_name);
				ft_error("Not a valid identifier\n");
			}
			ft_export_search(data->args[y], var_name, cpy_envp, data);
			free(var_name);
			y++;
		}
	}
	else
		ft_export_tri(cpy_envp, y - 1);
}
