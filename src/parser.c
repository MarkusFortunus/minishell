
#include "minishell.h"

int	ft_check_token(char **begin, char *end, char *tok)
{
	char	*s;

	if (!*begin || !end || !tok)
		return (0);
	s = *begin;
	while (s < end && ft_strchr(" \n\t", *s)) // passer les espace
		s++;
	*begin = s;
	return (*s && ft_strchr(tok, *s));
}

t_cmd	*ft_parsecmd(char *s)
{
	char	*end_s;
	t_cmd	*cmd;

	if (!s)
		return (NULL);
	end_s = s + ft_strlen(s);
	cmd = ft_parsepipe(&s, end_s);
	ft_check_token(&s, end_s, ""); // chaine vide, pour mettre ptr a jour sur char suivant
	if (s != end_s)//check si il reste char invalid non parser par autre fonction
	{
		ft_printf("Erreur syntax\n");
		exit(EXIT_FAILURE);
	}
	ft_nulterminate_str(cmd);
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
			exit(EXIT_FAILURE);
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
	int			token;
	size_t		argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (!*begin || !end || !begin)
		return (NULL);
	ret = ft_build_exec_node(begin, end);
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = ft_parseredir(ret, begin, end);
	while (!ft_check_token(begin, end, "|"))
	{
		token = ft_add_token(begin, end, &cmd->argv[argc], &cmd->eargv[argc]);
		if (token == 0)
			break ;
		argc++;
		ret = ft_parseredir(ret, begin, end);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return (ret);
}
