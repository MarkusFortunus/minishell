
#include "minishell.h"

// int	ft_check_token(char **begin, char *end, char *tok)
// {
// 	char	*s;

// 	if (!*begin || !end || !tok)
// 		return (0);
// 	s = *begin;
// 	while (s < end && ft_strchr(" \n\t", *s)) // passer les espace
// 		s++;
// 	*begin = s;
// 	return (*s && ft_strchr(tok, *s));
// }

// pipe_cmd_t	*ft_parsecmd(char *s)
// {
// 	char	*end_s;
// 	pipe_cmd_t	*ecmd;

// 	if (!s)
// 		return (NULL);
// 	end_s = s + ft_strlen(s);
// 	ecmd = ft_parsepipe(&s, end_s);
// 	ft_check_token(&s, end_s, ""); // chaine vide, pour mettre ptr a jour sur char suivant
// 	if (s != end_s)//check si il reste char invalid non parser par autre fonction
// 	{
// 		ft_printf("Erreur syntax\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	//ft_nulterminate_str(ecmd);//a modifier
// 	return (ecmd);
// }

// pipe_cmd_t	*ft_parsepipe(char **begin, char *end)
// {
// 	//pipe_cmd_t	*ret = 0;
// 	t_data		*cmd = ft_calloc(1, sizeof(t_data));
// 	int			argc;
// 	int			token;

// 	if (!*begin || !end)
// 		return (NULL);
// 	//cmd = ft_parseexec(begin, end);
// 	// if (ft_check_token(begin, end, "|"))
// 	// {
// 	// 	ft_add_token(begin, end, 0, 0);
// 	// 	cmd = ft_build_pipe_node(cmd, ft_parsepipe(begin, end));
// 	// }
// 	argc = 0;
// 	//ret = ft_parseredir(ret, begin, end);
// 	while (!ft_check_token(begin, end, "|"))
// 	{
// 		token = ft_add_token(begin, end, &cmd->args[argc], &cmd->eargs[argc]);
//  		// if (token == 0)
//  		// 	break ;
// 		argc++;
// 		//ret = ft_parseredir(ret, begin, end);
// 	}
// 	ft_printf("OK\n");
// 	cmd->args[argc] = 0;
//  	cmd->eargs[argc] = 0;
// 	cmd->arg_count = argc;
// 	pipe_cmd_t *new_node = ft_init_cmd_node(cmd->args[0], 0);
//   //  ft_pipe_cmd_add_back(&ret, new_node);
// 	return (new_node);
// }

// pipe_cmd_t	*ft_parseredir(pipe_cmd_t *node, char **begin, char *end)
// {
// 	int		tok;
// 	char	*cur;
// 	char	*end_cur;

// 	while (*begin > end)
// 	{
// 		tok = ft_add_token(begin, end, 0, 0);
// 		if (ft_add_token(begin, end, &cur, &end_cur) != 'a')
// 		{
// 			ft_printf("missing file\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (tok == '<')
// 			node->type = REDIR_I;
// 		else if (tok == '>')
// 			node->type = REDIR_O;
// 		else if (tok == '+')
// 			node->type = APPEND;
// 		else if (tok == '-')
// 			node->type = HEREDOC;
// 	}
// 	node->file_name = cur;
// 	return (node);
// }

// t_cmd	*ft_parseexec(char **begin, char *end)
// {
// 	int			token;
// 	size_t		argc;
// 	t_execcmd	*cmd;
// 	t_cmd		*ret;

// 	if (!*begin || !end || !begin)
// 		return (NULL);
// 	ret = ft_build_exec_node(begin, end);
// 	cmd = (t_execcmd *)ret;
// 	argc = 0;
// 	ret = ft_parseredir(ret, begin, end);
// 	while (!ft_check_token(begin, end, "|"))
// 	{
// 		token = ft_add_token(begin, end, &cmd->argv[argc], &cmd->eargv[argc]);
// 		if (token == 0)
// 			break ;
// 		argc++;
// 		ret = ft_parseredir(ret, begin, end);
// 	}
// 	cmd->argv[argc] = 0;
// 	cmd->eargv[argc] = 0;
// 	return (ret);
// }
