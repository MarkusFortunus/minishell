#include "minishell.h"

static void find_all_dollar_double_quotes(char **str, int i, dol_qt_t *data)
{
	int dollar_pos;

	data->end_double = search_index('\"', *str, i); // del
	dollar_pos = search_index('$', *str, i);
	while (dollar_pos != -1 && data->end_double != -1 && dollar_pos < data->end_double)
	{
		if (((*str)[dollar_pos + 1] && ft_strncmp(&(*str)[dollar_pos], "$?", 2) && (*str)[dollar_pos + 1] && isalpha((*str)[dollar_pos + 1])) || ((*str)[i + 1] && isdigit(((*str)[dollar_pos + 1])) && (*str)[dollar_pos - 1] != '\\'))
			replace_dollar_to_var(str, data, dollar_pos);
		else if (!ft_strncmp(&(*str)[dollar_pos], "$?", 2))
			pipe_return_err(str, dollar_pos);
		else if ((*str)[dollar_pos + 1] != ' ' && (*str)[dollar_pos + 1] != '\"')
		{
			ft_memmove(&(*str)[dollar_pos], &(*str)[dollar_pos + 1], ft_strlen(&(*str)[dollar_pos]));
			break;
		}
		else
			break;
		data->end_double = search_index('\"', *str, dollar_pos);
		dollar_pos = search_index('$', *str, dollar_pos);
		
	}
}

static int ft_process_check_quote(char **str, int i, char type_of_quote, dol_qt_t *data)
{
    if ((*str)[i] == type_of_quote)
    {
		ft_memmove(&(*str)[i], &(*str)[i + 1], ft_strlen(&(*str)[i]));
        while (((*str)[i] && (*str)[i] != '\"' && (*str)[i] != '$' && type_of_quote == '\"') || ((*str)[i] && (*str)[i] != '\'' && type_of_quote == '\''))
            i++;
		if (type_of_quote == '\"')
		{
			data->end_double = search_index(type_of_quote, *str, i);
			if(data->end_double == -1 && ft_error(NULL, NULL, "Missing closing quote\n", 2))
				return (0);
		}
        if (type_of_quote == '\"' && (*str)[i] == '$')
            find_all_dollar_double_quotes(str, i, data);
        else if ((*str)[i] != type_of_quote && ft_error(NULL, NULL, "Missing closing quote\n", 2))
            return (0);
        if (type_of_quote != '\'')
			ft_memmove(&(*str)[data->end_double], &(*str)[data->end_double] + 1, ft_strlen(&(*str)[data->end_double]));
		else
			data->end_single = search_index('\'', *str, i);
        return (2);
    }
    return (1);
}

static void verif_can_check_quote(char **str, dol_qt_t *data, int *i)
{
    if (data->end_double == -1 || (data->end_double <= *i && (*str)[*i] == '\"') || data->end_double < *i)
		data->return_var = ft_process_check_quote(str, *i, '\'', data);
    if (data->return_var == 0 || data->return_var == 2)
        return ;
    if (data->end_single == -1 || data->end_single <= *i)
        data->return_var = ft_process_check_quote(str, *i, '\"', data);
}

static void verif_is_dollar(char **str, dol_qt_t *data, int *i)
{
    if ((*str)[*i] == '\\' && (*str)[*i + 1] && (*str)[*i + 1] == '$')
	{
		ft_memmove(&(*str)[*i], &(*str)[*i + 1], ft_strlen(&(*str)[*i]));
		(*i)++;
		data->return_var = 2;
		return ;
	}	
	if ((*str)[*i] == '$' && ft_strncmp(&(*str)[*i], "$?", 2) && ft_isprint((*str)[*i + 1]) && (*str)[*i + 1] != ' ' && (data->end_single == -1 || data->end_single <= *i))
	{
		replace_dollar_to_var(str, data, *i);
		return ;
	}
	else if (!ft_strncmp(&(*str)[*i], "$?", 2) && (data->end_single == -1 || data->end_single <= *i))
		pipe_return_err(str, *i);
	data->return_var = 1;
}

static void ft_check_quote_dollar_process(char **str, dol_qt_t *data)
{
	int i;
	
	i = 0;
    while ((*str)[i] != '\0')
    {
		if (i == data->end_single)
			ft_memmove(&(*str)[data->end_single], &(*str)[data->end_single + 1], ft_strlen(&(*str)[data->end_single]));
        verif_is_dollar(str, data, &i);
        if (data->return_var == 2)
            continue ;
        else if (data->return_var == 0)
            break;
        verif_can_check_quote(str, data, &i);
        if (data->return_var == 2)
            continue ;
        else if (data->return_var == 0)
            break;
        i++;
        data->return_var = 1;
    }
}
int	ft_check_quote_dollar(char **str, char **env)
{
    dol_qt_t *data;
    int return_var;
	char *newstr;
    data = malloc(sizeof(dol_qt_t));
    init_dol_qt(data, str, env);
	newstr = ft_strdup(*str);
	ft_check_quote_dollar_process(&newstr, data);
    return_var = data->return_var;
	free(*str);
	*str = newstr;
    free(data);
    return (return_var);
}
