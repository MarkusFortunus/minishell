
#ifndef STRUCT_H
# define STRUCT_H

# define EXEC    1
# define PIPE    2
# define REDIR   3
# define APPEND  4
# define HEREDOC 5

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
	int		fd[2];
	int		arg_count;
	int		type; //type : exec pipe append heredoc...
	char	*file; //le nom du file sera là en cas de redirection dans un fichier 
	pid_t	pid;
}			t_data;

/**
 * @param type Type de commande (pipe exec redir, ..)
**/
// typedef struct s_cmd
// {
// 	int	type;
// }		t_cmd;

// //structure des "noeuds" pipe de l'arborescence 
// //contient un ptr vers noeuds de gauche et droite qui contiendrons les cmmade executable ou les redirections
// typedef struct s_pipecmd
// {
// 	int		type;
// 	t_cmd	*left;
// 	t_cmd	*right;
// }			t_pipecmd;

// //structure des noeuds contenant les commande final avec les argument dans un tableau
// // (argv sera copié dans le **args de data)
// typedef struct s_execcmd
// {
// 	int		type;
// 	char	**argv;
// 	char	**eargv;
// 	size_t	argc;
// 	size_t	count;
// }			t_execcmd;

// //structure des redirections, le nom du fichier sera copié dans le file de data
// typedef struct s_redircmd
// {
// 	int		type;
// 	t_cmd	*cmd;
// 	char	*file;
// 	char	*efile;
// 	int		mode; //O_RDONLY, ..
// 	int		fd;
// }			t_redircmd;

typedef struct  pipe_cmd_s {
    int fd[2];
    char **env;
    char *file_name;
    int pos;
    bool is_last;
    char *cmd;
    bool trunc_outfile;
	struct pipe_cmd_s	*next;	
} pipe_cmd_t;


#endif
