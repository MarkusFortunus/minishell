
#include "minishell.h"

// void	ft_get_cmd(t_cmd *cmd, t_data *data)
// {
// 	t_pipecmd	*pcmd;
// 	t_execcmd	*ecmd;
// 	t_redircmd	*rcmd;

// 	//checker si !cmd et si cmd->type == 0
// 	if (cmd->type == EXEC)
// 	{
// 		int i = 0;
// 		ecmd = (t_execcmd *)cmd;
// 		if (ecmd->argv[0] != NULL)
// 		{
// 			data->args = ecmd->argv;
// 			while (data->args[i])
// 			{
// 				//ft_printf("%s\n", data->args[i]);
// 				i++;
// 			}
// 			data->arg_count = i;
// 			//ft_check_cmd(data);
// 		}
// 		// else
// 		// 	return ; gestion erreur??
// 	}
// 	else if (cmd->type == PIPE)
// 	{
// 	 	pcmd = (t_pipecmd *)cmd;
// 	 	ft_get_cmd(pcmd->left, data);
// 	 	ft_get_cmd(pcmd->right, data);
// 	}
// 	else if (cmd->type == REDIR || cmd->type == APPEND || cmd->type == HEREDOC)
// 	{
// 		//la redirection simple > a l'air de marcher, mais pas le reste
// 		rcmd = (t_redircmd *)cmd;
// 		data->file = rcmd->file;
// 		if (cmd->type == APPEND)
// 			data->type = APPEND;
// 		if (cmd->type == HEREDOC)
// 			data->type = HEREDOC;
// 		//gerer HEREDOC
// 		//ft_printf("%s type: %d\n", data->file, data->type);
// 		close(rcmd->fd);
// 		ft_get_cmd(rcmd->cmd, data);
// 	}
// }