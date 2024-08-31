#include "minishell.h"

int search_index(char type_of_char, char *str, int i)
{
	char *search;
	int pos;
	search = ft_strchr(&str[i], type_of_char);
	if (!search)
		pos = -1;
	else
		pos = search - str;
	return (pos);
}

bool pipe_return_err(char **str, int i) {
	char *newstr;
	char *temp;
	char *itoa;

	newstr = ft_substr(*str, 0, i);
	itoa = ft_itoa(exit_stat);
	temp = ft_strjoin(newstr, itoa);
	free(itoa);
	free(newstr);
	newstr = ft_strjoin(temp, &(*str)[i + 2]);
	free(temp);
	free(*str);
	*str = newstr;
	return true;
}

void init_dol_qt(dol_qt_t *data, char **str, char **env) {
    data->end_double = -1;
    data->end_single = -1;
    data->str_start = *str;
	data->env = env;
	data->ienv = 0;
    data->return_var = -1;
}