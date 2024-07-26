
#ifndef STRUCT_H
# define STRUCT_H

// # define EXEC			1
// # define REDIR_I		2
// # define REDIR_O		3
// # define APPEND			4
// # define HEREDOC		5
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
	char	*input;
	char	**args;
	char	**envp;
	int		arg_count;
	int		type; //type : exec pipe append heredoc...
	char	*file; //le nom du file sera là en cas de redirection dans un fichier 
	pid_t	pid;
	int 	(*fd)[2];
}			t_data;

/**
 * @param type Type de commande (pipe exec redir, ..)
**/
typedef struct  pipe_cmd_s {

    char **env;
    char *file_name;
	char **stdin_file;
	char **stdout_file;
    int pos;
    char *cmd;
// ca doit etre un array pour checker plusieurs redirection lequel est trunc ou pas;	
    bool *trunc;//append
	bool *heredoc;
	int		stdout;
	int		stdin;
	struct pipe_cmd_s	*next;	
	// int (*fd)[2];
} pipe_cmd_t;

#endif
