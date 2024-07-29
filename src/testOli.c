
#include "minishell.h"


void pipe_cmd(pipe_cmd_t *p_data, t_data *data)
{
	if (!(p_data->pos == 0 && !p_data->next))
	{
		close_pipes(data->fd, p_data->pos, data->arg_count - 1);
		if (p_data->pos == 0 && (dup2(data->fd[0][1], STDOUT_FILENO) == -1) && printf("problemhakka")) // ici
    	    exit(EXIT_FAILURE);
		else if (!p_data->next && (dup2(p_data->stdout, STDOUT_FILENO) == -1 || dup2(data->fd[p_data->pos - 1][0], STDIN_FILENO) == -1) && printf("problem"))
    	    exit(EXIT_FAILURE);
		else if (p_data->pos != 0 && p_data->next && (dup2(data->fd[p_data->pos][1], STDOUT_FILENO) == -1 || dup2(data->fd[p_data->pos - 1][0], STDIN_FILENO) == -1) && printf("problem"))
    		exit(EXIT_FAILURE);
		if (p_data->pos == 0)
			close(data->fd[0][1]);
		else
			close(data->fd[p_data->pos - 1][0]);
	}
	// if (!stdout_file(p_data))
	// 	return false;
	// else if (!stdin_file(p_data))
	// 	return false;
	if (!ft_check_cmd(data, p_data))
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
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
		pipe_cmd(p_data, data);
	int status;
	waitpid(pid, &status, 0);
	if (!(p_data->pos == 0 && !p_data->next))
		close_fd(p_data, data);
	 if (WIFEXITED(status)) 
	 {
		exit_status = WEXITSTATUS(status);
        if (exit_status == EXIT_SUCCESS)
            return true;
        else
            return false;
    }
	else
		false;
	return true;
}
