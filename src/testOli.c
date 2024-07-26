
#include "minishell.h"



bool first_cmd(pipe_cmd_t *p_data, t_data *data)
{
	// if (!stdin_file(p_data))
	// 	return false;
    if (!p_data->file_name)
    {
		close_pipes(data->fd, 0, data->arg_count - 1);
        if ((dup2(data->fd[0][1], STDOUT_FILENO) == -1) && printf("problemhakka")) // ici
            return false;
		close(data->fd[0][1]);
    }
	if (ft_check_cmd(data, p_data))
		exit(0);
    return true;
}

bool last_cmd(pipe_cmd_t *p_data, t_data *data)
{
	// if (!stdout_file(p_data))
	// 	return false;
	if (!p_data->file_name)
	{
		// close(data->fd[arg_count - 1][1]);
		close_pipes(data->fd, p_data->pos, data->arg_count - 1); // peut etre problem
    	if ((dup2(p_data->stdout, STDOUT_FILENO) == -1 || dup2(data->fd[p_data->pos - 1][0], STDIN_FILENO) == -1) && printf("problem"))
    	    return false;
		close(data->fd[p_data->pos - 1][0]);
	}
	if (ft_check_cmd(data, p_data))
		exit(0);
    return true;
}

bool in_between_cmd(pipe_cmd_t *p_data, t_data *data)
{
		close_pipes(data->fd, p_data->pos, data->arg_count - 1); // peut etre problem
    	if ((dup2(data->fd[p_data->pos][1], STDOUT_FILENO) == -1 || dup2(data->fd[p_data->pos - 1][0], STDIN_FILENO) == -1) && printf("problem"))
    	    return false;
		//close(data->fd[p_data->pos - 1][0]); // i think not
		close(data->fd[p_data->pos][0]);
	if (ft_check_cmd(data, p_data))
		exit(0);
	return true;
}

bool only_one_cmd(pipe_cmd_t *p_data, t_data *data)
{
	// if (!stdout_file(p_data))
	// 	return false;
	// else if (!stdin_file(p_data))
	// 	return false;
	printf("lollol");
	if (ft_check_cmd(data, p_data))
		exit(0);
	return true;
}
// lit log et ecrit erreur 
// grep "erreur" < log.txt > erreurs.txt
// redirige: wc -l < fichier.txt
// bash-3.2$ ls | grep i > test.txt | grep i
// bash-3.2$ ls | grep i < test.txt | grep i
bool each_pipe(pipe_cmd_t *p_data, t_data *data)
{  
	int pid;

	pid = fork();
	if (!pid)
	{
		if (p_data->pos == 0 && !p_data->next && !only_one_cmd(p_data, data))
			return false;
		if (p_data->pos == 0)
    	{
			printf("%s\n", p_data->cmd);
    	    // if (p_data->type == HEREDOC && !heredoc(p_data, data))
    	    //     return false;
    	    if (!first_cmd(p_data, data))
				return false;
    	}
    	else if (p_data->file_name || !p_data->next)
    	{
    	    if (!last_cmd(p_data, data))
    	        return false;
    	}
    	else
			in_between_cmd(p_data, data);
	}
	int status;
	waitpid(pid, &status, 0);
	close_fd(p_data, data);
	return true;
}
