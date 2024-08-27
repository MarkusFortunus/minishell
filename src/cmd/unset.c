#include "minishell.h"

void	ft_unset(pipe_cmd_t *node, t_data *data)
{
	int	i;

	i = 0;
	while (node->env[i])
	{
		if (strncmp(node->env[i], node->cmd_arg[1], ft_strlen(node->cmd_arg[1]))
			== 0 && node->env[i][ft_strlen(node->cmd_arg[1])] == '=')
		{
			while (node->env[i + 1])
			{
				free(node->env[i]);
				node->env[i] = ft_strdup(node->env[i + 1]);
				if (!node->env[i] && printf("Error with allocing memory\n"))
					return ;
				i++;
			}
			free(node->env[i]);
			node->env[i] = ft_strdup(NULL);
			free(node->env[i + 1]);
			ft_free(data->envp, NULL);
			data->envp = ft_get_envp_cpy(node->env);
			return ;
		}
		i++;
	}
}
