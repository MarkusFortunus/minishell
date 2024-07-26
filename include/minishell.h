#ifndef MINISHELL_H
# define MINISHELL_H

# define GREEN "\033[92m"
# define RES "\033[0m"
# define RED "\033[91m"
# define PROMPT GREEN"minishell$ "RES

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "../libft/libft.h"
#include "../libft/ft_printf/ft_printf.h"
#include "struct.h"


bool	ft_check_cmd(t_data *data, pipe_cmd_t *node);
void	ft_env_cmd(char **envp);
void	ft_export_cmd(t_data *data);
void	ft_exit_cmd(t_data *data);
void	ft_pwd_cmd();
char	**ft_split_cmd(char *str, char sep);
char	**ft_get_envp_cpy(char	**envp);
bool	ft_execute(char **envp, t_data *data, pipe_cmd_t *node);
char	*ft_search_path(char *command, char **envp);
void	ft_free(char **to_free, char *exit);
void	ft_error(char *error);
int		ft_chdir(char *path);
void	ft_export_tri(char **cpy_envp, int y);
void	ft_export_search(char *export, char *name, char **env);
void	ft_export_modif(char *export, char ***env);
void	ft_export_add(char *export, char ***env);
size_t	ft_equal_sign(char *str);
int		ft_valid_name(char *str);
void	ft_unset(t_data *data);
void	ft_remove_export(char **envp, int x);
void	ft_free_lst(pipe_cmd_t *node);
int		ft_check_quote_dollar(char *str, char **env);
int		ft_process_check_quote(char *str, char **env, char type_of_quote);
int		ft_count_arg(char **tab);

// parsing

void		ft_add_back(pipe_cmd_t **lst, pipe_cmd_t *new);
pipe_cmd_t	*ft_init_cmd_node(char *arg, int i, int arg_count);
void		ft_init_redir_node(pipe_cmd_t *node);
char		**ft_split_quote(char const *s, char *token);
void		ft_parse_cmd(t_data *data);
void		ft_parse_pipe(t_data *data);
void		ft_parse_redir(pipe_cmd_t *node);
void		ft_check_redir_syntax(char *input, pipe_cmd_t *node);
void		ft_count_redir(char *input, int *in, int *out);

//test pipe Oli

//char *find_path_cmd(char *cmd);
//bool do_cmd(char *cmd, char **env);
bool process_child(pipe_cmd_t *p_data, int fd2[2], t_data *data);
bool process_parent(int fd[2], int fd2[2]);
bool first_cmd(pipe_cmd_t *p_data, t_data *data);
bool last_cmd(pipe_cmd_t *p_data, t_data *data);
bool in_between_cmd(pipe_cmd_t *p_data, t_data *data);
bool each_pipe(pipe_cmd_t *p_data, t_data *data);
bool heredoc(pipe_cmd_t *p_data, t_data *data);
void close_fd(pipe_cmd_t *p_data, t_data *data);
bool stdin_file(pipe_cmd_t *p_data);
bool stdout_file(pipe_cmd_t *p_data);
void	close_pipes(int fd[][2], int wichpipe, int nbr_pipe);




//siganux
void	ft_handle_sigint(int signal);
void	ft_child_handle_signal(int signal);


#endif