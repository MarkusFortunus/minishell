
#include "minishell.h"

// pipe_cmd_t	*ft_nulterminate_str(pipe_cmd_t *node)
// {
// 	// int			i;
	
// 	// i = 0;
// 	if (node == 0)
// 		return (0);
// 	// if (cmd->type == EXEC)
// 	// {
// 	// 	ecmd = (t_execcmd *)cmd;
// 	// 	while (ecmd->eargv[i])
// 	// 		i++;
// 	// 	ecmd->eargv[i] = 0;
// 	// }
// 	if (node->type != 0)
// 		node->file_name = 0;
// 	return (node);
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