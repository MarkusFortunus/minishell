#include "minishell.h"

static void replace_to_empty(char *str, char *strcpy, char *env)
{
	//char *cpy_pos;
	int i = 0;
	if (!env)
	{
		while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
			i++;
		if (!str[i])
			ft_strlcpy(str, "", 1);
		else
			ft_strlcpy(str, &str[i], ft_strlen(&str[i]) + 2);
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
	while (str[size_of_var] != ' ' && str[size_of_var] != '\"' && str[size_of_var] != '\0' && (ft_isalpha(str[size_of_var]) || ft_isdigit(str[size_of_var])) && str[size_of_var] != '$' ) // et enlever els meta character
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

static void ft_find_all_dollar_double_quotes(char *str, char **env)
{
	char *dollar_pos;
	char *next_double_quotes;

	next_double_quotes = ft_strchr(str, '\"');
	//*end_double = ft_strchr(str, '\"');
	ft_memmove(&next_double_quotes[0], &next_double_quotes[1], ft_strlen(str));
	while ((dollar_pos = ft_strchr(str, '$')) && dollar_pos < next_double_quotes)
	{
		if (ft_strncmp(str, "$?", 2) && (ft_isalpha(*(str + 1)) || ft_isdigit(*(str + 1))) && *(str - 1) != '\\')
			ft_replace_dollar_to_var(dollar_pos, env);
		else if (!ft_strncmp(str, "$?", 2))
			ft_pipe_return_err(str);
		str++;
	}
	str--;
}

int ft_process_check_quote(char *str, char **env, char type_of_quote, char **end_double)
{
    if (*str == type_of_quote)
    {
		ft_memmove(&str[0], &str[1], ft_strlen(str));
       //while (*str && *str != type_of_quote || ((*str != '$' && type_of_quote != '\'')))
       while ((*str && *str != '\"' && *str != '$' && type_of_quote == '\"') || (*str && *str != '\'' && type_of_quote == '\''))
            str++;
		if ( type_of_quote == '\"' && (*end_double = ft_strchr(str, '\"')) && *str == '$')
			ft_find_all_dollar_double_quotes(str, env);
        else if (*str != type_of_quote)
		{
			ft_error(NULL, NULL, "Missing closing quote", 2);
			return 0;
		}	
		else if (type_of_quote != '\'')
			ft_memmove(&str[0], &str[1], ft_strlen(str));
		return (2);
    }
	return (1);
}

bool ft_pipe_return_err(char *str) {
	ft_memmove(&str[0], &str[1], ft_strlen(str));
	if (exit_status == 0)
		str[0] = '0';
	else
		ft_strlcpy(&str[0], ft_itoa(exit_status), ft_strlen(ft_itoa(exit_status)) + 1);
	return true;
}

void verif_can_check_quote(char **str, char **end_double, int *return_var, char **env, char **end_single)
{
	if (!*end_double || (*end_double <= *str && **end_double == '\"') || *end_double < *str) // peut etre mettre un autre truc 
		*return_var = ft_process_check_quote(*str, env, '\'', end_double);
	if (*return_var == 0)
		return ;
	if (*return_var == 2)
	{
		*end_single = ft_strchr(*str, '\'');
		ft_memmove(*end_single, *end_single + 1, ft_strlen(*end_single));
		return ;
	}
	if (!*end_single || *end_single <= *str)
		*return_var = ft_process_check_quote(*str, env, '\"', end_double);
}

void verif_is_dollar(char **str, int *return_var, char **env, char **end_single)
{
	if (**str == '\\' && *(*str + 1) == '$')
	{
		ft_memmove(*str, *str + 1, ft_strlen(*str));
		(*str)++;
		*return_var = 2;
		return ;
	}	
	if (**str == '$' && ft_strncmp(*str, "$?", 2) && ft_isprint(*(*str + 1)) && *(*str + 1) != ' ' && (!*end_single || *end_single <= *str))
	{
		*return_var = (ft_replace_dollar_to_var(*str, env));
		if (*return_var == 0)
			return ;
		*return_var = 2;
		return ;
	}
	else if (!ft_strncmp(*str, "$?", 2))
		ft_pipe_return_err(*str);
	*return_var = 1;
}
int	ft_check_quote_dollar(char **str, char **env)
{
	int i = 0;
	int return_var;
	char *newstr = ft_strdup(*str);
	char *end_double = NULL;
	char *end_single = NULL;
	free(*str);
	*str = newstr;
    while (*newstr)
    {

		verif_is_dollar(&newstr, &return_var, env, &end_single) ;
		if (return_var == 2)
			continue;
		else if (return_var == 0)
			break;
		verif_can_check_quote(&newstr, &end_double, &return_var, env, &end_single);
		if (return_var == 0)
			break ;
		if (return_var == 2)
			continue;
		i++;
       	newstr++;
		return_var = 1;
    }
    return (return_var);
}

//114
// 115 116
// echo '"$USER"'
// 152