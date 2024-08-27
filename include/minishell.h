#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR "\001\033[0;34m\002\001\033[1m\002"
# define RES "\001\e[0m\022\002"
# define RED "\033[91m"
# define EMOJI "\001\033\[33m\002\001\u26A1\002"
# define BLUE " \001\033\[33m\002\001\u26A1\002\001\033[0;34m\002"
# define SYNTAX_TOKEN "syntax error near unexpected token 'newline'\n"
# define DIR ": is a directory\n"

//GREEN"minishell$ "RES
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

// parsing quote
int		ft_check_quote_dollar(char **str, char **env);
int		ft_process_check_quote(char *str, char **env, char type_of_quote, char **end_double);
int		ft_check_quote(char *str);

// pipe
bool	start_pipe(pipe_cmd_t *p_data, t_data *data);
int		ft_do_cmd(pipe_cmd_t *node, t_data *data);
bool	each_pipe(pipe_cmd_t *p_data, t_data *data);
void	close_fd(pipe_cmd_t *p_data, t_data *data);
bool	stdin_file(pipe_cmd_t *p_data);
bool	stdout_file(pipe_cmd_t *p_data);
void	close_pipes(int fd[][2], int wichpipe, int nbr_pipe);
bool	ft_heredoc(char *eof, int nbr_eof);

// execute
bool	ft_execute(char **envp, pipe_cmd_t *node);
char	*ft_search_path(char *command, char **envp);
int		ft_err_code(int exit_value);

// builtin
void	ft_env_cmd(char **envp);
int		ft_exit_cmd(t_data *data, pipe_cmd_t *node, bool need_exit);
void	ft_pwd_cmd();
char	**ft_split_cmd(char *str, char sep);
char	**ft_get_envp_cpy(char	**envp);
int		ft_chdir(char *path, pipe_cmd_t *node, t_data *data);
void	ft_unset(pipe_cmd_t *node, t_data *data);
bool	is_builtin(pipe_cmd_t *node);
void	ft_echo(pipe_cmd_t *node);

// export
int		ft_export_cmd(pipe_cmd_t *node, t_data *data);
void	ft_remove_export(char **envp, int x);
void	ft_export_tri(char **cpy_envp, int y);
void	ft_export_search(char *export, char *name, pipe_cmd_t *node, t_data *data);
void	ft_export_modif(char *export, char ***env);
void	ft_export_add(char *export, char ***env);
int		ft_valid_name(char *str);
size_t	ft_eq_sign(char *str);
void	find_equal(char *str, int *equal_pos);

// error and free
void 	ft_free_data(t_data *data);
void	ft_free(char **to_free, char *exit);
int		ft_error(char *cmd, char *syntaxe, char *error, int exit_value);
void	ft_free_lst(pipe_cmd_t *node);
void	ft_free_exit(t_data *data, pipe_cmd_t *node);

// parsing
int			ft_count_arg(char **tab);
char		**ft_split_quote(char const *s, char *token);
int			ft_parse_cmd(t_data *data);
char		*ft_skip_quote(char *s);
char		*ft_skip_space(char *s);
int			ft_is_space(char *s);
int			ft_split_arg(pipe_cmd_t *node);
void		ft_fill_stdio_file(pipe_cmd_t *node, char *input);
int			ft_check_directory(pipe_cmd_t *node);
int			ft_check_pipe(t_data *data);

// parsing list
void		ft_add_back(pipe_cmd_t **lst, pipe_cmd_t *new);
pipe_cmd_t	*ft_init_cmd_node(char *arg, int i, pipe_cmd_t *start_lst, t_data *data);
void		ft_init_redir_node(pipe_cmd_t *node);

// redir
bool	ft_pipe_return_err(char *str);
void		ft_count_redir(char *input, int *in, int *out);
int		ft_parse_pipe(t_data *data);
int			ft_parse_redir(pipe_cmd_t *node);
bool		ft_check_redir_syntax(char *input, pipe_cmd_t *node);

//siganux
void	ft_handle_sigint(int signal);
void	ft_child_handler(int signal);
void	ft_heredoc_handler(int signal);

#endif