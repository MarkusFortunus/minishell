#include "minishell.h"

void close_pipes1(int fd[][2], int count) {
    for (int i = 0; i < count; i++) {
        close(fd[i][0]);
        close(fd[i][1]);
    }
}

int pipe_cmd(pipe_cmd_t *p_data, t_data *data)
{
	if (!(data->arg_count == 1))
	{
		if (p_data->pos == 0 && (dup2(data->fd[0][1], STDOUT_FILENO) == -1) && printf("problemhakka")) // ici
    	    exit(EXIT_FAILURE);
		else if (!p_data->next && (dup2(data->fd[p_data->pos - 1][0], STDIN_FILENO) == -1) && printf("lolproblem"))
    	    exit(EXIT_FAILURE);
		else if (p_data->pos != 0 && p_data->next && (dup2(data->fd[p_data->pos][1], STDOUT_FILENO) == -1 || dup2(data->fd[p_data->pos - 1][0], STDIN_FILENO) == -1) && printf("lolaproblem"))
    		exit(EXIT_FAILURE);
	}
	close_pipes1(data->fd, data->arg_count - 1);
	if (!stdout_file(p_data))
		exit(EXIT_SUCCESS);
	else if (!stdin_file(p_data))
		exit(EXIT_SUCCESS);
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
	while (p_data)
	{
		if ((pid[i] = fork()) == -1)
			return false; // faire ca mieux
		signal(SIGINT, ft_child_handler);
		signal(SIGQUIT, ft_child_handler);
		if (!pid[i])
		{
			pipe_cmd(p_data, data);
		}
		i++;
		p_data = p_data->next;
	}
	if (i > 1)
	{
		close(data->fd[i - 2][1]);
		close(data->fd[i - 2][0]);
	}
	i--;
	while (i >= 0)
	{
		waitpid(pid[i], &status, 0);
		exit_status = ft_err_code(status);
		if (i > 1)
		{
			close(data->fd[i - 2][1]);
			close(data->fd[i - 2][0]);
		}
		i--;
	}
	close_pipes1(data->fd, data->arg_count - 1);
	return true;
}

bool start_pipe(pipe_cmd_t *p_data, t_data *data)
{
	if (data->arg_count == 1 && is_builtin(p_data))
	{
		exit_status = ft_do_cmd(p_data, data);
		// ft_printf("ex_stat: %d\n", exit_status);	// faire dequoi avec la valeur de retour
	}
	else
		each_pipe(p_data, data);
	if (data->arg_count > 1)
		free(data->fd);
	ft_free(data->args, NULL);
	return true;
}