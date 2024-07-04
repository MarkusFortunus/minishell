/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:38:48 by fcornill          #+#    #+#             */
/*   Updated: 2024/07/04 15:28:59 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_check_quote(char *str)
{
    while (*str)
    { 
        if (*str == '\"')
        {
            str++;
            while (*str && *str != '\"')
                str++;
            if (*str != '\"') {
                ft_printf("Missing closing quote\n");
                return (0);
            }
        }
        else if (*str == '\'')
        {
            str++;
            while (*str && *str != '\'')
                str++;
            if (*str != '\'') {
                ft_printf("Missing closing quote\n");
                return (0);
            }
        }
        str++;
    }
    ft_printf("ok quote\n");
    return (1);
}

/*static char *ft_strndup(const char *s, size_t n) {
    char *result = (char *)malloc(n + 1);
    if (result) {
        ft_strlcpy(result, s, n);
        result[n] = '\0';
    }
    return result;
}

char	**ft_split_cmd(char *str, char sep)
{
	int		i;
	int		arg_index;
	char	*arg_start;
	bool in_single_quote = false, in_double_quote = false; //a mettre ds un enum ou struct?
	
	char	**args = ft_calloc(1024, sizeof(char *));
	i = 0;
	arg_index = 0;
	arg_start = str;

    while (str[i]) {
        if (str[i] == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        } else if (str[i] == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        } else if (str[i] == sep && !in_single_quote && !in_double_quote) {
            args[arg_index++] = ft_strndup(arg_start, &str[i] - arg_start);
            arg_start = &str[i + 1];
        }
        i++;
    }

    // Ajouter le dernier token
    if (arg_start != &str[i]) {
        args[arg_index++] = ft_strndup(arg_start, (&str[i] - arg_start) + 1);
    }

    args[arg_index] = NULL;
    return (args);
}*/
	
int	ft_add_token(char **begin, char *end, char **cur, char **end_cur)
{
	char	whitespace[] = " \t\r\n";
	char	sep[] = "<|>";
	char	*s;
	int		ret;

	s = *begin;
	while (s < end && ft_strchr(whitespace, *s))
		s++;
	if (cur)   // pour pouvoir revenir en arriere pour reanalyser une section(" et $ ?)
		*cur = s;
	ret = *s;
	if (*s != 0)
	{
		if (*s == '|')
			s++;
		else if (*s == '>')
		{
			s++;
			if (*s == '>')
			{
				ret = '+'; //retourner + si append (+ajopter gestion d'erreur)
				s++;
			}
		}
		else if (*s == '<')
		{
			s++;
			if (*s == '<')
			{
				ret = 'H'; //retourner - si heredoc (gestion d'erreur)
				s++;
			}
		}
		else
		{
			ret = 'a';
			while (s < end && !ft_strchr(whitespace, *s) && !ft_strchr(sep, *s))
				s++;
		}
		if (end_cur)
			*end_cur = s;
		while (s < end && ft_strchr(whitespace, *s))
			s++;
		*begin = s;
	}
	return (ret);
}


/*int ft_token(char **begin, char *end, char **old, char **end_old)
{
    char whitespace[] = " \t\r\n";
    char sep[] = "<|>";
    char *token;
    int ret;

    // Initialiser `token` avec le premier token trouvé.
    token = ft_strtok(*begin, whitespace);

    // Si aucun token trouvé, retourner 0.
    if (token == NULL)
        return 0;

    // Sauvegarder la position actuelle si `old` n'est pas NULL.
    if (old)
        *old = token;

    // Déterminer le type de token.
    if (ft_strchr(sep, *token))
    {
        ret = *token;
        if (*token == '>' && *(token + 1) == '>')
        {
            ret = '+';
            token += 2;
        }
        else if (*token == '<' && *(token + 1) == '<')
        {
            ret = '-';
            token += 2;
        }
        else
			token++;
    }
    else
		ret = 'a';

    // Sauvegarder la fin de l'ancien token si `end_old` n'est pas NULL.
    if (end_old)
        *end_old = *token;

    // Passer les espaces blancs restants.
    while (*token && ft_strchr(whitespace, *token))
        token++;

    // Mettre à jour `begin` avec la nouvelle position de `token`.
    *begin = token;

    return (ret);
}*/

char	*ft_strtok(char *str, const char *sep)
{
	static char	*buffer;
	char		*token;
	
	if (str != NULL)
		buffer = str;
	if (buffer == NULL)
		return (NULL);
	while (*buffer && ft_strchr(sep, *buffer) != NULL)
		buffer++;
	if (*buffer == '\0')
	{
		buffer = NULL;
		return (NULL);
	}
	token = buffer;
	while (*buffer && ft_strchr(sep, *buffer) == NULL)
		buffer++;
	if (*buffer)
	{
		*buffer = '\0';
		buffer++;
	}
	//ft_printf("%s\n", buffer);
	return (token);
}

