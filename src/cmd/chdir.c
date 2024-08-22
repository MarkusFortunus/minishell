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
		return (ft_error("cd: ", NULL, "No such  file or directory\n", 1));
	//change cwd in env. maybe use getcwd(cwd, sizeof(cwd)) ?
	return (0);
}
