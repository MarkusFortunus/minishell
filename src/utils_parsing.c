
#include "minishell.h"

// t_cmd	*ft_nulterminate_str(t_cmd *cmd)
// {
// 	int			i;
// 	t_pipecmd	*pcmd;
// 	t_redircmd	*tcmd;
// 	t_execcmd	*ecmd;
	
// 	i = 0;
// 	if (cmd == 0)
// 		return (0);
// 	if (cmd->type == EXEC)
// 	{
// 		ecmd = (t_execcmd *)cmd;
// 		while (ecmd->eargv[i])
// 			i++;
// 		ecmd->eargv[i] = 0;
// 	}
// 	if (cmd->type == REDIR)
// 	{
// 		tcmd = (t_redircmd *)cmd;
// 		tcmd->efile = 0;
// 	}
// 	else if (cmd->type == PIPE)
// 	{
// 		pcmd = (t_pipecmd *)cmd;
// 		ft_nulterminate_str(pcmd->left);
// 		ft_nulterminate_str(pcmd->right);
// 	}
// 	return (cmd);
// }

// size_t	ft_count_argc(char **begin, char *end)
// {
// 	char	*tmp;
// 	size_t 	argc;
// 	int		token;
// 	char	*cur;
// 	char	*end_cur;

// 	tmp = *begin;
// 	argc = 0;
// 	while (!ft_check_token(&tmp, end, "|")) {
//         if ((token = ft_add_token(&tmp, end, &cur, &end_cur)) == 0)
//             break;
//         argc++;
//         tmp++;
//     }
// 	return (argc);
// }