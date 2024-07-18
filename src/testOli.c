
#include "minishell.h"
// difference entre >> et >
// > le contenu va etre ecraser tendit que lautre seulement ajouter en dessous


char *find_path_cmd(char *cmd)
{
    char **path;
    int i;
    char *try_path = NULL;
    char *cmd_path;    i = 0;
    // not sure about getenv because not the right environnement probably
    path = ft_split(getenv("PATH"), ':');
    while (path[i])
    {
        try_path = ft_strjoin(path[i], "/");
        cmd_path = ft_strjoin(try_path, cmd);
        free(try_path);
        if (access(cmd_path, X_OK) == 0)
            return cmd_path;
        free(cmd_path);
        i++;
    }
    return NULL;
}

bool do_cmd(char *cmd, char **env)
{
    char *cmd_path;
    char **cmd_split;    
	if (!(cmd_split = ft_split(cmd, ' ')))
        return false, printf("error allocating memory");
    if (!(cmd_path = find_path_cmd(cmd_split[0])))
	{
		printf("command not found\n");
		free(cmd_split);
        return false;
	}
    if (execve(cmd_path, cmd_split, env) == -1 && printf("failed to execute command"))
    {
        free(cmd_split);
        free(cmd_path);
        return false;
    }
    free(cmd_path); // maybe leaks
    return true;
}

bool process_child(pipe_cmd_t *p_data, int fd2[2])
{    if ((dup2(p_data->fd[0], STDIN_FILENO) == -1 || dup2(fd2[1], STDOUT_FILENO) == -1 || close(p_data->fd[1]) == -1 || close(fd2[0]) == -1) && printf("problem"))
        return false;
    if (!do_cmd(p_data->cmd, p_data->env))
        return false;
	return true;
    // execve
}

bool process_parent(int fd[2], int fd2[2])
{
    int bytes_read;
    char *buffer[10];
    if ((dup2(fd2[0], STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1 || close(fd2[1]) == -1 || close(fd[0]) == -1) && printf("problem"))
        return false;
    // copy one pipe to another
    while ((bytes_read = read(fd2[0], buffer, sizeof(buffer))))
        write(fd[1], buffer, bytes_read);
    // write fd2 into fd;
	return true;
}

bool first_cmd(pipe_cmd_t *p_data)
{
    int file;    if (p_data->file_name)
    {
        file = open(p_data->file_name, 0);
        if (file == -1 && printf("error failed to open file"))
            return false;
        if ((dup2(file, STDIN_FILENO) == -1 || dup2(p_data->fd[1], STDOUT_FILENO) == -1 || close(p_data->fd[0]) == -1) && printf("problem"))
            return false;
    }
    else
    {
        if ((dup2(p_data->fd[1], STDOUT_FILENO) == -1 || close(p_data->fd[0]) == -1) && printf("problem"))
            return false;
    }
    if (!do_cmd(p_data->cmd, p_data->env))
        return false;
    return true;
}

bool last_cmd(pipe_cmd_t *p_data)
{
    int file;    if (p_data->trunc_outfile)
        file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else
        file = open("output.txt", O_WRONLY | O_CREAT, 0777);
    if ((dup2(file, STDOUT_FILENO) == -1 || close(p_data->fd[1]) == -1) && dup2(p_data->fd[0], STDIN_FILENO) && printf("problem"))
        return false;
    if (!do_cmd(p_data->cmd, p_data->env))
        return false;
    return true;
}

void in_between_cmd(pipe_cmd_t *p_data)
{
    int fd2[2];
    int pid;    pipe(fd2);
    pid = fork();
    if (pipe(fd2) == -1 || (pid = fork() == -1))
        return ;
    if (pid == 0)
        process_child(p_data, fd2);
    wait(NULL);
    process_parent(p_data->fd, fd2);
}//bool each_pipe(char *file_name, int fd[2], int pos, bool trunc_outfile, char *cmd, char **env, int nbr_cmd)

bool each_pipe(pipe_cmd_t *p_data)
{
    if (p_data->pos == 0)
    {
        if (!first_cmd(p_data))
            return false;
    }
    else if (p_data->file_name || p_data->is_last)
    {
        if (!last_cmd(p_data))
            return false;
    }
    else
        in_between_cmd(p_data);
	return true;
}