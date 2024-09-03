#include "minishell.h"

static int pipe_cmd(pipe_cmd_t *p_data, t_data *data, int i)
{
	if (i != 0)
	{
		dup2(data->prev, STDIN_FILENO);
		close(data->prev);
	}
	if (i < data->arg_count - 1)
	{
		close(data->fd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
	}
	if (stdout_file(p_data))
		exit(exit_stat);
	else if (stdin_file(p_data))
		exit(exit_stat);
	if (is_builtin(p_data))
		exit(ft_do_cmd(p_data, data));
	else
		ft_execute(data->envp, p_data);
	exit(EXIT_SUCCESS);
}

bool each_pipe(pipe_cmd_t *p_data, t_data *data)
{  
	int pid[data->arg_count];
	int i = 0;
	int status = 0;
	int	i_val = 0;

	while (p_data)
	{
		if (pipe(data->fd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
        }
		if ((pid[i] = fork()) == -1)
			return false;
		signal(SIGINT, ft_child_handler);
		signal(SIGQUIT, ft_child_handler);
		if (!pid[i])
			pipe_cmd(p_data, data, i);
		if (i != 0)
        	close(data->prev);
		if (i < data->arg_count - 1)
		{	
			close(data->fd[1]);
			data->prev = data->fd[0];
		}
		i++;
		p_data = p_data->next;
	}
	i--;
	i_val = i;
	while (i >= 0)
	{
		waitpid(pid[i], &status, 0);
		if (i == i_val)
			exit_stat = ft_err_code(status);
		else
		{
			if (WIFSIGNALED(status))
			exit_stat = (128 + WTERMSIG(status));
		}
		i--;
	}
	return true;
}
