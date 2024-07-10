/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:34:46 by fcornill          #+#    #+#             */
/*   Updated: 2024/07/09 15:10:45 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_token(char	**begin, char *end, char *tok) //verifie si un caractere est present dans la string tok
{
	char	*s;
	
	if (!*begin || !end || !tok)
		return (0);
	s = *begin;
	while (s < end && ft_strchr(" \n\t", *s)) //passer les espace
		s++;
	*begin = s;
	return (*s && ft_strchr(tok, *s));//vrai si s != \0 et que l'on a trouvé le tok
}


t_cmd	*ft_parsecmd(char *s)
{
	if (!s)
		return (NULL);
	char	*end_s;
	t_cmd	*cmd;

	end_s = s + ft_strlen(s); //mettre poiteur sur \0
	cmd = ft_parsepipe(&s, end_s);
	ft_check_token(&s, end_s, "");//chaine vide, juste pour mettre a jour le pointeur s sur prochain caractere
	if (s != end_s)//si il reste un caratere qui n'a pas ete parsé par les autres fonctions, il est invalide
	{
		ft_printf("Erreur syntax\n");
		exit (EXIT_FAILURE);
	}
	ft_nulterminate_str(cmd);
	ft_printf("ok nulterminate\n");
	return (cmd);
}


t_cmd	*ft_parsepipe(char **begin, char *end)
{
	t_cmd	*cmd;

	if (!*begin || !end)
		return (NULL);
	cmd = ft_parseexec(begin, end);
	if (ft_check_token(begin, end, "|"))
	{
		ft_add_token(begin, end, 0, 0);
		cmd = ft_build_pipe_node(cmd, ft_parsepipe(begin, end));
	}
	return (cmd);
}

t_cmd	*ft_parseredir(t_cmd *cmd, char **begin, char *end)
{
	int		tok;
	char	*cur;
	char	*end_cur;

	while (ft_check_token(begin, end, "<>"))
	{
		tok = ft_add_token(begin, end, 0, 0);
		if (ft_add_token(begin, end, &cur, &end_cur) != 'a')
		{
			ft_printf("missing file\n");
			exit (EXIT_FAILURE);
		}
		if (tok == '<')
			cmd = ft_build_redir_node(REDIR, cmd, cur, end_cur);
		else if (tok == '>')
			cmd = ft_build_redir_node(REDIR, cmd, cur, end_cur);
		else if (tok == '+')
			cmd = ft_build_redir_node(APPEND, cmd, cur, end_cur);
		 else if (tok == '-')
		 	cmd = ft_build_redir_node(HEREDOC, cmd, cur, end_cur);
	}
	return (cmd);
}

t_cmd	*ft_parseexec(char **begin, char *end)
{
	char		*cur;
	char		*end_cur;
	int			token;
	size_t		argc;
	t_execcmd	*cmd;
	t_cmd		*ret;
	size_t		count;

	if (!*begin || !end)
		return (NULL);
	count = ft_count_argc(begin, end);
	ret = ft_build_exec_node(count);
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = ft_parseredir(ret, begin, end);
	while (!ft_check_token(begin, end, "|"))
	{
		if ((token = ft_add_token(begin, end, &cur, &end_cur)) == 0)
			break ;
		cmd->argv[argc] = cur;
		cmd->eargv[argc] = end_cur;
		ft_printf("cmd de argv: %s\n", cmd->argv[argc]);
		argc++;
		ret = ft_parseredir(ret, begin, end);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	count = 0;
	return (ret);
}