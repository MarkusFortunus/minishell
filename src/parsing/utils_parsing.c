#include "minishell.h"

int	ft_count_arg(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_skip_quote(char *s)
{
	char	quote;

	quote = *s;
	s++;
	while (*s && *s != quote)
		s++;
	if (*s)
		s++;
	return (s);
}

char	*ft_skip_space(char *s)
{
	while (*s && ft_strchr(" \t\r\v\f", *s))
		s++;
	return (s);
}

int	ft_is_space(char *s)
{
	while (*s)
	{
		if (*s != ' ' && *s != '\t' && *s != '\v' && *s != '\f' && *s != '\r')
			return (0);
		else
			s++;
	}
	return (1);
}
