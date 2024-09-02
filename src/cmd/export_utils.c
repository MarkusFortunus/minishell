#include "minishell.h"

int	ft_valid_name(char *str)
{
	int	i;

	i = 0;
	// while (ft_isalpha(str[i]) || ft_isdigit(str[i]))		
	// 	i++;
	// if (str[i] != '=')
	// 	return 0;
	// i++;
	// while (ft_isalpha(str[i]) || ft_isdigit(str[i]))		
	// 	i++;
	// if (!str[i])
	// 	return 1;
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

size_t	ft_eq_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	find_equal(char *str, int *equal_pos)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			*equal_pos = i;
			return ;
		}
		i++;
	}
	*equal_pos = -1;
}
