#include "minishell.h"

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
	//change cwd in env. maybe use getcwd(cwd, sizeof(cwd)) ?
	return (0);
}
