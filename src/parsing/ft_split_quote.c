
#include "minishell.h"

// static char	*skip_quote(char *s, char quote)
// {
// 	s++;
// 	while (*s && *s != quote)
// 		s++;
// 	if (*s)
// 		s++;
// 	if (*s && (*s == 39 || *s == 34))
// 		return (skip_quote(s, *s));
// 	return (s);
// }

static char *skip_quote(char *s, char quote)
{
	s++;
	while (*s && *s != quote) {
		s++;
	}
	if (*s == quote)
		s++;
	return (s);
}


/* Fonction qui compte le nombre de string qui seront créé */
static int	count_str_quote(char *s, char *token)
{
	int	str_nbr;

	str_nbr = 0;
	while (*s)
	{
		while (*s && ft_strchr(token, *s))
			s++;
		if (*s)
			str_nbr++;
		if (*s == 39)
			s = skip_quote(s, 39);
		else if (*s == 34)
			s = skip_quote(s, 34);
		while (*s && !ft_strchr(token, *s))
			s++;
	}
	return (str_nbr);
}

static char	*find_next_str(char *s, char *token)
{
	char	quote;
	
	while (*s && !ft_strchr(token, *s))
	{
		if (39 == *s || 34 == *s)
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
			if (*s && *s == quote)
				s++;
		}
		else
			s++;
	}
	return (s);
}

static void split_it_quote(char *s, char ***final_array, char *token)
{
	char	*end_str;
	int		i;
	
	i = 0;
	while (*s)
	{
		while (*s && ft_strchr(token, *s))
			s++;
		if (*s)
		{
			end_str = find_next_str(s, token);
			(*final_array)[i] = ft_substr(s, 0, (end_str - s));
			if (!(*final_array)[i])
			{
				ft_free(*final_array, NULL);
				return ;
			}
			i++;
			s = end_str;
		}
	}
	(*final_array)[i] = 0;
}

/* Fonction qui sépare un string en une série de sous-string */
char	**ft_split_quote(char const *s, char *token)
{
	char	**final_array;
	char	*s_copy;

	if (!s)
		return (0);
	s_copy = ft_strdup(s);
	final_array = ft_calloc(count_str_quote(s_copy, token) + 1, sizeof(char *));
	if (!final_array)
	{
		free(s_copy);
		return (0);
	}
	split_it_quote(s_copy, &final_array, token);
	free(s_copy);
	s_copy = NULL;
	return (final_array);
}