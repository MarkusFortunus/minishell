#include "minishell.h"

static void replace_to_empty(char *str, char *strcpy, char *env)
{
	char *cpy_pos;

	if (!env)
	{
		cpy_pos = ft_strchr(strcpy, ' ');
		if (cpy_pos == NULL)
			ft_strlcpy(str, "", 1);
		else 
			ft_strlcpy(str, cpy_pos, ft_strlen(cpy_pos) + 1);
	}
	free(strcpy);
}
static int ft_replace_dollar_to_var(char *str, char **env)
{
	int i;
	int size_of_var;
	int len_of_replace_var;
	char *strcpy;

	ft_memmove(&str[0], &str[1], ft_strlen(str));
	strcpy = ft_strdup(str);
	if (!strcpy)
		return 0;
	i = 0;
	size_of_var = 0;
	while (str[size_of_var] != ' ' && str[size_of_var] != '\"' && str[size_of_var] != '\0')
		size_of_var++;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, size_of_var) == 0 && env[i][size_of_var] == '=')
		{
			len_of_replace_var = ft_strlen(env[i]) - size_of_var;
			ft_strlcpy(str, &env[i][size_of_var + 1], len_of_replace_var);
			ft_strlcat(str, (strcpy + size_of_var), (ft_strlen(&strcpy[size_of_var]) + len_of_replace_var));
			break;
		}
		i++;
	}
	replace_to_empty(str, strcpy, env[i]);
	return 1;
}

static int ft_find_all_dollar_double_quotes(char *str, char **env)
{
	char *dollar_pos;
	char *last_double_quotes;

	last_double_quotes = ft_strrchr(str, '\"');
	while ((dollar_pos = ft_strchr(str, '$')) && dollar_pos < last_double_quotes)
		ft_replace_dollar_to_var(dollar_pos, env);
	return 1;
}
// le process de regarder si il y a des quotes et si "$" remplace le mot avec la var d'env
int ft_process_check_quote(char *str, char **env, char type_of_quote)
{
    if (*str == type_of_quote)
    {
        str++;
        while (*str && *str != type_of_quote && (type_of_quote == '\'' || (*str != '$' && type_of_quote != '\'')))
            str++;
		if (*str == '$' && type_of_quote == '\"' && ft_find_all_dollar_double_quotes(str, env) == 1)
			return 1;
        else if (*str != type_of_quote) {
            ft_printf("Missing closing quote\n");
        	return (0);
        }
		else
			return (1);
    }
	return (2);
}

int	ft_check_quote_dollar(char *str, char **env)
{
	int return_var;

    while (*str)
    {
		if (*str == '$')
			return_var = (ft_replace_dollar_to_var(str, env));
		return_var = ft_process_check_quote(str, env, '\'');
		if (return_var == 0 || return_var == 1)
			break ;
		return_var = ft_process_check_quote(str, env, '\"');
		if (return_var == 0 || return_var == 1)
			break ;
        str++;
		return_var = 1;
    }
    return (return_var);
}