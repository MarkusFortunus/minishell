
#include "minishell.h"

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
    return (1);
}

//ajouter fonction pour gerer $ avec ""

// int	ft_add_token(char **begin, char *end, char **cur, char **end_cur)
// {
// 	char	sep[] = "<|>";
// 	char	*s;
// 	int		ret;

// 	s = *begin;
// 	while (s < end && ft_strchr(" \n\t", *s))
// 		s++;
// 	if (cur)
// 		*cur = s;
// 	ret = *s;
// 	if (*s != 0)
// 	{
// 		if (*s == '\'' || *s == '\"')
// 		{
// 			s++;
// 			while (s < end && *s != '\'' && *s != '\"') // chercher la fin de la citation
//                 s++;
//             if (s < end && (*s == '\'' || *s == '\"')) // si la fin de la citation est trouvée
//                 s++;
// 		}
// 		if (*s == '|')
// 			//s++;
// 		else if (*s == '>')
// 		{
// 			s++;
// 			if (*s == '>')
// 			{
// 				ret = '+'; //retourner + si append (+ajopter gestion d'erreur)
// 				s++;
// 			}
// 		}
// 		else if (*s == '<')
// 		{
// 			s++;
// 			if (*s == '<')
// 			{
// 				ret = '-'; //retourner - si heredoc (gestion d'erreur)
// 				s++;
// 			}
// 		}
// 		else
// 		{
// 			ret = 'a';
// 			while (s < end && !ft_strchr(" \n\t", *s) && !ft_strchr(sep, *s))
// 				s++;
// 		}
// 		if (end_cur)
// 			*end_cur = s;
// 		while (s < end && ft_strchr(" \n\t", *s))
// 			s++;
// 		*begin = s;
// 	}
// 	return (ret);
// }


