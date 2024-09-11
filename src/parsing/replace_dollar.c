/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:26:23 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 15:38:06 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_to_empty(char **str, int i, t_dol_qt *data)
{
	int		ivar;
	char	*temp;
	char	*newstr;

	ivar = i;
	if (!data->env[data->ienv])
	{
		if (ft_isdigit((*str)[ivar]) && ft_memmove(&(*str)[ivar], &(*str)[ivar
				+ 1], ft_strlen(&(*str)[ivar]) + 1))
			return ;
		while ((*str)[ivar] && (ft_isalpha((*str)[ivar])
				|| ft_isdigit((*str)[ivar])))
			ivar++;
		temp = ft_substr(*str, 0, i);
		newstr = ft_strjoin(temp, &(*str)[ivar]);
		free(temp);
		free(*str);
		*str = newstr;
	}
	data->ienv = 0;
}

static void	replace_process(int i, int size_var, t_dol_qt *data, char **str)
{
	char	*newstr;
	char	*temp;

	newstr = ft_substr(&(*str)[0], 0, i);
	temp = ft_strjoin(newstr, &data->env[data->ienv][size_var + 1]);
	free(newstr);
	newstr = ft_strjoin(temp, &(*str)[i + size_var]);
	free(temp);
	free(*str);
	*str = newstr;
}

void	replace_dollar_to_var(char **str, t_dol_qt *data, int i)
{
	int	size_var;

	ft_memmove(&(*str)[i], &(*str)[i + 1], ft_strlen(&(*str)[i]));
	size_var = 0;
	while (((*str)[size_var + i] != '\0' && (*str)[size_var + i] != ' '
			&& (*str)[size_var + i] != '\"' && ft_isalpha((*str)[size_var + i]))
		|| (ft_isdigit((*str)[size_var + i]) && (*str)[size_var + i] != '$'))
		size_var++;
	while (data->env[data->ienv] != NULL)
	{
		if (!ft_strncmp(data->env[data->ienv], &(*str)[i], size_var)
			&& data->env[data->ienv][size_var] == '=')
		{
			replace_process(i, size_var, data, str);
			break ;
		}
		data->ienv++;
	}
	replace_to_empty(str, i, data);
}
