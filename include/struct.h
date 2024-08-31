
#ifndef STRUCT_H
# define STRUCT_H

// # define REDIR_INPUT	1
// # define REDIR_OUTPUT	2
// # define APPEND			3
// # define HEREDOC		4

int exit_stat; // public var

typedef struct t_dol_qt
{
	int ienv;
    int return_var;
    char *str_start;
	char **env;
    int end_double;
    int end_single;
} dol_qt_t;

/**

 * @param input String de commandes.
 * @param args Liste d'arguments.
 * @param envp Environement.
 * @param fd Descipteurs de fichiers pipe.
 * @param pid ID process pour le fork.
 * @param arg_count nb d'arguments.
 * */
typedef struct s_data
{
	char 	*prompt; // needs to free it
	char	*input;
	char	**args;
	char	**envp;
	int		arg_count;
	char	*file; //le nom du file sera là en cas de redirection dans un fichier 
	pid_t	pid;
	int 	(*fd)[2];
}			t_data;

/**
 * @param x index de cmd_arg
**/
typedef struct  pipe_cmd_s {
	char 	*error;
	int		err_to_return;
    char **env;
	char **stdin_file; //<
	char **stdout_file;//>
	int stdin_count;
	int stdout_count;
	char	**cmd_arg;
    int pos;
    char *cmd;
	int	arg_cnt;
    bool *trunc;//append
	bool *heredoc;
	struct pipe_cmd_s	*next;
	struct pipe_cmd_s	*start_ls;
	int	x; //index de cmd_arg
	int	stdfd;
} pipe_cmd_t;

typedef struct s_heredoc
{
	char	*tmp_file;
	char	*filename;
	int		fd;
	int		id;
	int		status;
}	t_heredoc;

#endif
