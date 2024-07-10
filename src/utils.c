/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:09:10 by fcornill          #+#    #+#             */
/*   Updated: 2024/07/09 15:11:58 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Error function, print error message and exit
void	ft_error(char *error)
{
	write(2, "Error:\n", 8);
	write(2, error, ft_strlen(error));
	exit(1);
}

//Free un tableau. Exit si un message est ajouter. Sinon, mettre "NULL"
void	ft_free(char **to_free, char *exit)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	if (exit)
		ft_error(exit);
}

char	**ft_get_envp_cpy(char	**envp)
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

t_cmd	*ft_nulterminate_str(t_cmd *cmd)
{
	int			i;
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	
	i = 0;
	if (cmd == 0)
		return (0);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		while (ecmd->argv[i])
		{
			*ecmd->eargv[i] = 0;
			i++;
		}
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		ft_nulterminate_str(pcmd->left);
		ft_nulterminate_str(pcmd->right);
	}
	return (cmd);
}

size_t	ft_count_argc(char **begin, char *end)
{
	char	*tmp;
	size_t 	argc;
	int		token;
	char	*cur;
	char	*end_cur;

	tmp = *begin;
	argc = 0;
	while (!ft_check_token(&tmp, end, "|")) {
        if ((token = ft_add_token(&tmp, end, &cur, &end_cur)) == 0)
            break;
        argc++;
        tmp++;
    }
	ft_printf("argc : %d\n", argc);
	return (argc);
}


