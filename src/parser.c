/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:34:46 by fcornill          #+#    #+#             */
/*   Updated: 2024/07/04 15:39:06 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_token(char	**begin, char *end, char *tok) //verifie si un caractere est present dans la string tok
{
	char	whitespace[] = " \t\r\n";
	char	*s;
	
	if (!*begin || !end || !tok)
		return (0);
	s = *begin;
	while (s < end && ft_strchr(whitespace, *s))
		s++;
	*begin = s;
	return (*s && ft_strchr(tok, *s));//vrai si il reste qqchose a s et l'on a trouvé le tok
}


t_cmd	*ft_parsecmd(char *s)
{
	if (!s)
		return (NULL);
	char	*end_s;
	t_cmd	*cmd;

	end_s = s + ft_strlen(s);
	//cmd = ft_parseline(&s, end_s);
	cmd = ft_parsepipe(&s, end_s);
	ft_check_token(&s, end_s, "");
	if (s != end_s)
	{
		ft_printf("Erreur syntax\n");
		exit (EXIT_FAILURE);
	}
	ft_nulterminate_str(cmd);
	ft_printf("ok nulterminate\n");
	return (cmd);
}

/*t_cmd	*ft_parseline(char **begin, char *end)// transformer en parse QUOTE?
{
	t_cmd	*cmd;
	
	cmd = ft_parsepipe(begin, end);
	return (cmd);
}*/

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
			cmd = ft_build_redir_node(cmd, cur, end_cur, O_RDONLY, 0);
		else if (tok == '>')
			cmd = ft_build_redir_node(cmd, cur, end_cur, O_WRONLY|O_CREAT, 1);
		else if (tok == '+')
			cmd = ft_build_redir_node(cmd, cur, end_cur, O_WRONLY|O_CREAT, 1);
		// else if (tok == 'H')
		// 	cmd = 
	}
	return (cmd);
}

t_cmd	*ft_parseexec(char **begin, char *end)
{
	char		*cur;
	char		*end_cur;
	int			tokken;
	size_t		argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	
	if (!*begin || !end)
		return (NULL);
	ret = ft_build_exec_node();
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = ft_parseredir(ret, begin, end);
	while (!ft_check_token(begin, end, "|"))
	{
		if ((tokken = ft_add_token(begin, end, &cur, &end_cur) == 0))
			break ;
		cmd->argv[argc] = cur;
		cmd->eargv[argc] = end_cur;
		ft_printf("cmd de argv: %s\n", cmd->argv[argc]);
		argc++;
		if (argc >= MAX_ARGS)
		{
			ft_printf("too many args\n");
			exit (EXIT_FAILURE);
		}
		ret = ft_parseredir(ret, begin, end);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	ft_printf("ret: %x\n", ret);
	return (ret);
}