
#include "minishell.h"

void	ft_get_cmd(t_cmd *cmd, t_data *data)
{
	t_pipecmd	*pcmd;
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;

	//checker si !cmd et si cmd->type == 0
	if (cmd->type == EXEC)
	{
		int i = 0;
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] != NULL)
		{
			data->args = ecmd->argv;
			while (data->args[i])
			{
				//ft_printf("%s\n", data->args[i]);
				i++;
			}
			data->arg_count = i;
			ft_check_cmd(data);
		}
		// else
		// 	return ; gestion erreur??
	}
	else if (cmd->type == PIPE)
	{
		int fd[2];
	 	pcmd = (t_pipecmd *)cmd;
		if (pipe(fd) < 0)
			return ft_error("pipe\n");
		pid_t pid_left = fork();
		if (pid_left == 0)
		{
			close(fd[0]);
			if (dup2(fd[1], 1) == -1 || close(fd[1]) == -1)
				return ft_error("pipe cmd left\n");
	 		ft_get_cmd(pcmd->left, data);
			exit(EXIT_SUCCESS);
		}
		pid_t pid_right = fork();
		if (pid_right == 0)
		{
			close(fd[1]);
			if (dup2(fd[0], 0) == -1 || close(fd[0]) == -1)
				return ft_error("pipe cmd right\n");
	 		ft_get_cmd(pcmd->right, data);
			exit(EXIT_SUCCESS);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid_left, NULL, 0);
        waitpid(pid_right, NULL, 0);
	}
	else if (cmd->type == REDIR || cmd->type == APPEND || cmd->type == HEREDOC)
	{
		//la redirection simple > a l'air de marcher, mais pas le reste
		rcmd = (t_redircmd *)cmd;
		data->file = rcmd->file;
		if (cmd->type == APPEND)
			data->type = APPEND;
		if (cmd->type == HEREDOC)
			data->type = HEREDOC;
		//gerer HEREDOC
		//ft_printf("%s type: %d\n", data->file, data->type);
		close(rcmd->fd);
		ft_get_cmd(rcmd->cmd, data);
	}
}