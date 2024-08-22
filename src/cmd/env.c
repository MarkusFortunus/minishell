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
