#include "minishell.h"

static void replace_to_empty(char **str, int i, dol_qt_t *data)
{
	int ivar;
	char *temp;
	char *newstr;

	ivar = i;
	if (!data->env[data->ienv])
	{
		if (ft_isdigit((*str)[ivar]) && memmove(&(*str)[ivar], &(*str)[ivar + 1], ft_strlen(&(*str)[ivar]) + 1))
			return ;
		while ((*str)[ivar] && (ft_isalpha((*str)[ivar]) || ft_isdigit((*str)[ivar])))
			ivar++;
		temp = ft_substr(*str, 0, i);
		newstr = ft_strjoin(temp, &(*str)[ivar]);
		free(temp);
		free(*str);
		*str = newstr;
	}
	data->ienv = 0;
}

static void    replace_process(int i, int size_var, dol_qt_t *data, char **str)
{
    char *newstr;
    char *temp;

    newstr = ft_substr(&(*str)[0], 0, i);
	temp = ft_strjoin(newstr, &data->env[data->ienv][size_var + 1]);
	free(newstr);
	newstr = ft_strjoin(temp, &(*str)[i + size_var]);
	free(temp);
    free(*str);
    *str = newstr;
}

void replace_dollar_to_var(char **str, dol_qt_t *data, int i)
{
    int size_var;

	memmove(&(*str)[i], &(*str)[i + 1], ft_strlen(&(*str)[i]));
    size_var = 0;
    while (((*str)[size_var + i] != '\0' && (*str)[size_var + i] != ' ' && (*str)[size_var + i] != '\"'  && isalpha((*str)[size_var + i])) || (isdigit((*str)[size_var + i]) && (*str)[size_var + i] != '$' ))
        size_var++;
    while(data->env[data->ienv] != NULL)
    {
        if (!ft_strncmp(data->env[data->ienv], &(*str)[i], size_var) && data->env[data->ienv][size_var] == '=')
        {
            replace_process(i, size_var, data, str);
            break;           
        }
        data->ienv++;
    }
	replace_to_empty(str, i, data);

}