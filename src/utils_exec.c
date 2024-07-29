

#include "../include/minishell.h"

static int		ft_echo_check(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	if (i > 0)
		return (1);
	return (0);
}

void	ft_echo(pipe_cmd_t *node)
{
	char	*start;
	bool	flag;
	int		i;

	i = 6;
	flag = false;
	if (!ft_strncmp(&node->cmd[5], "-n", 2))
	{
		while (node->cmd[i] == 'n')
			i++;
		if (!ft_echo_check(&node->cmd[i + 1]))
			return ;
		start = (node->cmd + (i + 1));
		flag = true;
	}
	else
		start = (node->cmd + 5);
	printf("%s", start);
	if (flag == false)
		printf("\n");
}

//Trouve la position du sign '=' (Peut etre adapter pour trouver n'importe quel signe)
size_t	ft_equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}


//Fonction pour verifier si le nom de la variable est valide. Si oui, retourne 1
int	ft_valid_name(char *str)
{
	int		i = 0;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

char	**ft_get_envp_cpy(char **envp)
{
	char	**cpy;
	int		y;

	y = 0;
	while (envp[y])
		y++;
	cpy = ft_calloc(y + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	y = 0;
	while (envp[y])
	{
		cpy[y] = ft_strdup(envp[y]);
		y++;
	}
	return (cpy);
}
