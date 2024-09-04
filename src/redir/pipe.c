

#include "minishell.h"

static void close_dup(t_data *data, int i)
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
	else
    	close(data->fd[0]);
}
static void pipe_cmd(pipe_cmd_t *p_data, t_data *data, int i)
{
	close_dup(data, i);
	if (stdout_file(p_data))
		exit(exit_stat);
	else if (stdin_file(p_data))
		exit(exit_stat);
	if (is_builtin(p_data))
	{
		exit_stat = ft_do_cmd(p_data, data);
		close(data->fd[1]);
		ft_exit_cmd(data, p_data, true);
	}
	if (stdout_file(p_data) || stdin_file(p_data))
		exit (exit_stat);
	else if (p_data->cmd_arg && p_data->cmd_arg[p_data->x])
		ft_execute(data, p_data);
	exit(EXIT_SUCCESS);
}


static int pipe_fork(t_data *data, int i, pipe_cmd_t *p_data)
{
	int pid;

	if (pipe(data->fd) == -1) 
	{
        perror("pipe");
        return false;
    }
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return false;
	}
	signal(SIGINT, ft_child_handler);
	signal(SIGQUIT, ft_child_handler);
	if (!pid)
		pipe_cmd(p_data, data, i);
	return (pid);
}

static void forkwait(t_data *data, int i, int pid[])
{
	int status;
	
	status = 0;
	while (--i >= 0)
	{
		if (waitpid(pid[i], &status, 0) != -1 && i == data->arg_count - 1)
			exit_stat = ft_err_code(status);
		else if ((i != data->arg_count - 1) && WIFSIGNALED(status) && (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT))
			exit_stat = (128 + WTERMSIG(status));
	}
}

static bool each_pipe(pipe_cmd_t *p_data, t_data *data)
{  
	int pid[data->arg_count];
	int i = 0;

	while (p_data)
	{
		pid[i] = pipe_fork(data, i, p_data);
		if (i != 0)
        	close(data->prev);
		if (i < data->arg_count)
		{
			close(data->fd[1]);
			data->prev = data->fd[0];
		}
		i++;
		p_data = p_data->next;
	}
	close(data->fd[0]);
	forkwait(data, i, pid);
	return true;
}

bool start_pipe(pipe_cmd_t *p_data, t_data *data)
{
	if (data->arg_count == 1 && is_builtin(p_data))
		exit_stat = ft_do_cmd(p_data, data);
	else
		each_pipe(p_data, data);
	return true;
}
