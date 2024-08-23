#include "minishell.h"

int	ft_chdir(char *path, pipe_cmd_t *node)
{
	char	*buf;
	int		i;

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
	buf = malloc(120);
	buf = getcwd(buf, 120);
	// printf("buf = %s\n", buf);
	ft_export_modif(ft_strjoin("PWD=", buf), &node->env);
	return (0);
}
