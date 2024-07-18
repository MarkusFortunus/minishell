

#include "minishell.h"

void	ft_env_cmd(char **envp)
{
	int	y;
	
	y = 0;
	while (envp[y])
	{
		if (ft_strchr(envp[y], '='))
			ft_printf("%s\n", envp[y]);
		y++;
	}
}

void	ft_exit_cmd(t_data *data)
{
	free(data->input);//sinon leaks dans le cas ou on ne tape de commande valide
	free(data);
	exit (EXIT_SUCCESS);
}

void	ft_pwd_cmd(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}

int	ft_chdir(char *path)
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
	if (chdir(path))
		perror("cd");
	return (0);
}