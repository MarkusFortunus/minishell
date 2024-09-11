/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:14:05 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 15:35:53 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_modif(char *export, char ***env)
{
	int		equal_pos;
	char	*line;
	int		i;

	equal_pos = 0;
	find_equal(export, &equal_pos);
	if (equal_pos == -1)
		return ;
	line = malloc(sizeof(char) * (ft_strlen(export) + 1));
	if (!line)
		return ;
	ft_strlcpy(line, export, ft_strlen(export) + 1);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], export, equal_pos) == 0
			&& (*env)[i][equal_pos] == '=')
		{
			free((*env)[i]);
			(*env)[i] = line;
			return ;
		}
		i++;
	}
}

void	ft_export_add(char *export, char ***env)
{
	char	**new_env;
	int		size_env;
	int		i;

	i = 0;
	size_env = 0;
	while ((*env)[size_env])
		size_env++;
	new_env = malloc((size_env + 2) * sizeof(char *));
	while (i != size_env)
	{
		new_env[i] = ft_strdup((*env)[i]);
		i++;
	}
	new_env[i] = ft_strdup(export);
	i++;
	new_env[i] = NULL;
	ft_free(*env, NULL);
	*env = new_env;
}

void	ft_export_tri(t_pipe_cmd *node, int y)
{
	char	*tmp;
	char	**cpy_envp;

	cpy_envp = ft_get_envp_cpy(node->env);
	while (cpy_envp[y])
	{
		if (ft_strncmp(cpy_envp[y], cpy_envp[y + 1], 1) > 0)
		{
			tmp = cpy_envp[y];
			cpy_envp[y] = cpy_envp[y + 1];
			cpy_envp[y + 1] = tmp;
			y = 0;
		}
		else
			y++;
	}
	y = 0;
	while (cpy_envp[y])
		ft_printf("declare -x %s\n", cpy_envp[y++]);
	ft_free(cpy_envp, NULL);
}

void	ft_export_search(char *exp, char *name, t_pipe_cmd *node, t_data *data)
{
	int	x;
	int	flag;

	x = 0;
	flag = 0;
	while (node->env[x])
	{
		if (!ft_strncmp(node->env[x], name, ft_strlen(name) + 1))
		{
			flag = 1;
			break ;
		}
		x++;
	}
	if (!flag)
		ft_export_add(exp, &node->env);
	else
		ft_export_modif(exp, &node->env);
	ft_free(data->envp, NULL);
	data->envp = ft_get_envp_cpy(node->env);
}

int	ft_export_cmd(t_pipe_cmd *node, t_data *data)
{
	char	*v_nm;
	int		y;

	y = node->x + 1;
	if (node->arg_cnt > 1)
	{
		while (node->cmd_arg[y])
		{
			v_nm = ft_substr(node->cmd_arg[y], 0, ft_eq_sign(node->cmd_arg[y]));
			if (!ft_valid_name(v_nm))
			{
				free(v_nm);
				return (ft_error(NULL, NULL, "Not a valid identifier\n", 1));
			}
			ft_export_search(node->cmd_arg[y], v_nm, node, data);
			free(v_nm);
			y++;
		}
	}
	else
		ft_export_tri(node, y - 1);
	return (0);
}
