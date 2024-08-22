#include "minishell.h"

static bool	ft_echo_check(char *str)
{
	while (*str)
	{
		if (*str != '-' && *str != 'n')
			return (false);
		str++;
	}
	return (true);
}

void	ft_echo(pipe_cmd_t *node)
{
	bool	flag;
	int		i;

	i = 1;
	flag = false;
	if (node->arg_cnt == 1)
	{
		printf("\n");
		return ;
	}
	if (!ft_strncmp(node->cmd_arg[1], "-n", 2))
	{
		while (ft_echo_check(node->cmd_arg[i]) == true)
			i++;
		flag = true;
	}
	while (node->cmd_arg[i])
	{
		if (ft_strlen(node->cmd_arg[i]) != 0)
		{
			if (node->cmd_arg[i + 1] == NULL)
				printf("%s", node->cmd_arg[i]);
			else
				printf("%s ", node->cmd_arg[i]);
		}
		i++;
	}
	if (flag == false)
		printf("\n");
}
