#include "minishell.h"

int	ft_chdir(char *path, pipe_cmd_t *node, t_data *data)
{
	char	*buf;
	int		i;

	i = 0;
	if (node->arg_cnt > 2)
		return(printf("cd: too many arguments\n"), 0);
	buf = malloc(120);
	buf = getcwd(buf, 120);
	ft_export_search(ft_strjoin("OLDPWD=", buf), "OLDPWD", node, data);
	if (ft_strchr(path, '.'))
	{
		while (path[i])
			i++;
		if (i == 1)
			return (0);
	}
	if (chdir(path))
		return (ft_error("cd: ", NULL, "No such  file or directory\n", 1));
	ft_bzero(buf, 120);
	buf = getcwd(buf, 120);
	ft_export_search(ft_strjoin("PWD=", buf), "PWD", node, data);
	return (0);
}
