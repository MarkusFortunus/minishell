/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dollar_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onault <onault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:25:41 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 15:55:36 by onault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_index(char type_of_char, char *str, int i)
{
	char	*search;
	int		pos;

	search = ft_strchr(&str[i], type_of_char);
	if (!search)
		pos = -1;
	else
		pos = search - str;
	return (pos);
}

bool	pipe_return_err(char **str, int i)
{
	char	*newstr;
	char	*temp;
	char	*itoa;

	newstr = ft_substr(*str, 0, i);
	itoa = ft_itoa(g_exit_stat);
	temp = ft_strjoin(newstr, itoa);
	free(itoa);
	free(newstr);
	newstr = ft_strjoin(temp, &(*str)[i + 2]);
	free(temp);
	free(*str);
	*str = newstr;
	return (true);
}

void	init_dol_qt(t_dol_qt *data, char **str, char **env)
{
	data->end_double = -1;
	data->end_single = -1;
	data->str_start = *str;
	data->env = env;
	data->ienv = 0;
	data->return_var = -1;
}

void	verif_can_check_quote(char **str, t_dol_qt *data, int *i)
{
	if (data->end_double == -1 || (data->end_double <= *i && (*str)[*i] == '\"')
		|| data->end_double < *i)
		data->return_var = ft_process_check_quote(str, *i, '\'', data);
	if (data->return_var == 0 || data->return_var == 2)
		return ;
	if (data->end_single == -1 || data->end_single <= *i)
		data->return_var = ft_process_check_quote(str, *i, '\"', data);
}
