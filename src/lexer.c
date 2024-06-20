/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:38:48 by fcornill          #+#    #+#             */
/*   Updated: 2024/06/20 13:37:59 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*int	check_quote(char *str)
{
	A ECRIRE!!!
}*/


/*void	get_flag(char *str, t_token *token) //ajouter un flag dans structure token pour chaque type de token
{
	int i = 0;
	
	while (str[i++])
	{
		if (str[i] == '|')
			token->pipe = 1;
	}
}*/


//NE SERT A RIEN POUR L'INSTANT/ C'ETAIT JUSTE UN TEST DE PARSING
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




//NE SERT A RIEN POUR L'INSTANT/ C'ETAIT JUSTE UN TEST DE PARSING
void	get_token(t_data *data, t_token *token) //sert a rien pour l'instant
{
	char	*str;

	str = data->input;
	while (*str)
	{
    	if (*str == '|')
        	token->pipe++;
    	else if (*str == '>')
    	{
        	if (*(str + 1) == '>') //attention au cas ou >>> ou >>>> le compte n'est pas bon!!!
            	token->append++;
        	else
            	token->right++;
    	}	
   		else if (*str == '<')
    	{
        	if (*(str + 1) == '<')//attention au cas ou >>> ou >>>> le compte n'est pas bon!!!
            	token->heredoc++;
        	else
            	token->left++;
    	}
    	str++;
	}
	// ft_printf("%d\n", token->pipe);
	// ft_printf("%d\n", token->right);
	// ft_printf("%d\n", token->left);
	// ft_printf("%d\n", token->heredoc);
	// ft_printf("%d\n", token->append);
}// essai non concluant
